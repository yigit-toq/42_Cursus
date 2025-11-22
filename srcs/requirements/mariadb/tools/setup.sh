#!/bin/sh
set -e

if [ -f /run/secrets/db_password ]; then
	MYSQL_PASSWORD=$(cat /run/secrets/db_password)
fi
if [ -f /run/secrets/db_root_password ]; then
	MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
fi

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld

DATADIR="/var/lib/mysql"

if [ -d "$DATADIR/$MYSQL_DATABASE" ]; then
	echo "[i] Veritabanı zaten mevcut. Başlatılıyor..."
else
	echo "[i] Veritabanı bulunamadı. Kurulum başlıyor..."

	mariadb-install-db --user=mysql --datadir=$DATADIR

	mysqld --user=mysql --datadir=$DATADIR --skip-networking &
	PID=$!

	until mariadb-admin ping > /dev/null 2>&1; do
		echo -n "."
		sleep 1
	done
	echo
	echo "[i] Geçici MariaDB sunucusu başlatıldı."

	SQL_SCRIPT="
	ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';
	CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\`;
	CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
	GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '$MYSQL_USER'@'%';
	CREATE USER IF NOT EXISTS '$WP_ADMIN_USER'@'%' IDENTIFIED BY '$WP_ADMIN_PASSWORD';
	GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '$WP_ADMIN_USER'@'%';
	FLUSH PRIVILEGES;
    "

	echo "[i] Veritabanı ve kullanıcılar oluşturuluyor..."
	echo $SQL_SCRIPT | mariadb -u root

	mariadb-admin -u root -p"$MYSQL_ROOT_PASSWORD" shutdown
	wait $PID
	echo "[i] Kurulum tamamlandı. Geçici sunucu kapatıldı."
fi

echo "[i] MariaDB sunucusu ön planda başlatılıyor..."
exec mysqld --user=mysql --datadir=$DATADIR
