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

	# 1. MariaDB veri dizinini (data directory) başlat
	mariadb-install-db --user=mysql --datadir=$DATADIR

	# 2. MariaDB sunucusunu geçici olarak arka planda başlat
	mysqld --user=mysql --datadir=$DATADIR --skip-networking &
	PID=$!

	# 3. Sunucunun başlamasını bekle
	until mariadb-admin ping > /dev/null 2>&1; do
		echo -n "."
		sleep 1
	done
	echo
	echo "[i] Geçici MariaDB sunucusu başlatıldı."

	# 4. .env dosyasından alınan değişkenlerle SQL komutlarını hazırla 
	#    - Root şifresini ayarla
	#    - Veritabanını oluştur
	#    - Ana WordPress kullanıcısını oluştur 
	#    - 'admin' içermeyen yönetici kullanıcıyı oluştur 
	#    - Yetkileri ver ve güncelle
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

# 7. MariaDB sunucusunu ön planda (PID 1 olarak) çalıştır
# 'exec' komutu, bu betiğin yerini mysqld işlemiyle değiştirir.
echo "[i] MariaDB sunucusu ön planda başlatılıyor..."
exec mysqld --user=mysql --datadir=$DATADIR