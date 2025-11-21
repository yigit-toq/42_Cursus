#!/bin/sh
set -e

mkdir -p /run/php

WP_PATH="/var/www/html"

if [ -f "$WP_PATH/wp-config.php" ]; then
	echo "[i] WordPress zaten kurulu. Başlatılıyor..."
else
	echo "[i] WordPress bulunamadı. Kurulum başlıyor..."

	apk add --no-cache curl
	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp

	cd $WP_PATH
	wp core download --allow-root --version=6.4.3 --locale=en_US

	echo "[i] MariaDB'nin hazır olması bekleniyor..."
	until mariadb -h "mariadb" -u "$MYSQL_USER" -p"$MYSQL_PASS" -e "SELECT 1;" > /dev/null 2>&1; do
		echo -n "."
		sleep 2
	done
	echo
	echo "[i] MariaDB hazır."

	wp config create --allow-root				\
		--dbname="$MYSQL_DATABASE"				\
		--dbuser="$MYSQL_USER"					\
		--dbpass="$MYSQL_PASS"				\
		--dbhost="mariadb"						\
		--dbprefix="wp_"

	wp core install --allow-root				\
		--url="$DOMAIN_NAME"					\
		--title="Inception Project"				\
		--admin_user="$WP_ADMIN_USER"			\
		--admin_password="$WP_ADMIN_PASS"	\
		--admin_email="$WP_ADMIN_EMAIL"

	wp user create --allow-root					\
		second user								\
		second@$DOMAIN_NAME						\
		--role=author							\
		--user_pass=123456

	chown -R nobody:nobody $WP_PATH

	echo "[i] WordPress kurulumu tamamlandı."
fi

echo "[i] PHP-FPM başlatılıyor..."
exec php-fpm82 -F
