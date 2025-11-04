#!/bin/sh
set -e

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld

# MariaDB veri dizini
DATADIR="/var/lib/mysql"

# Veritabanımızın ($MYSQL_DATABASE) zaten var olup olmadığını kontrol et
if [ -d "$DATADIR/$MYSQL_DATABASE" ]; then
	echo "[i] Veritabanı zaten mevcut. Başlatılıyor..."
else
	echo "[i] Veritabanı bulunamadı. Kurulum başlıyor..."

	# MariaDB veri dizinini (data directory) başlat
	mariadb-install-db --user=mysql --datadir=$DATADIR

	# MariaDB sunucusunu geçici olarak arka planda başlat
	mysqld --user=mysql --datadir=$DATADIR --skip-networking &
	PID=$!

	# Sunucunun başlamasını bekle
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

	# 5. SQL komutlarını çalıştır
	echo "[i] Veritabanı ve kullanıcılar oluşturuluyor..."
	echo $SQL_SCRIPT | mariadb -u root

	# 6. Geçici sunucuyu güvenli bir şekilde kapat
	mariadb-admin -u root -p"$MYSQL_ROOT_PASSWORD" shutdown
	wait $PID
	echo "[i] Kurulum tamamlandı. Geçici sunucu kapatıldı."
fi

# MariaDB sunucusunu ön planda (PID 1 olarak) çalıştır.
echo "[i] MariaDB sunucusu ön planda başlatılıyor..."
exec mysqld --user=mysql --datadir=$DATADIR
