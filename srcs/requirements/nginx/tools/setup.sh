#!/bin/sh
set -e

mkdir -p /etc/nginx/ssl

if [ ! -f /etc/nginx/ssl/nginx.crt ]; then
	echo "[i] NGINX: Kendi imzaladığımız SSL sertifikası oluşturuluyor..."
	
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
		-keyout /etc/nginx/ssl/nginx.key \
		-out /etc/nginx/ssl/nginx.crt \
		-subj "/C=TR/ST=Kocaeli/L=Gebze/O=42School/CN=$DOMAIN_NAME"
	else
	echo "[i] NGINX: SSL sertifikası zaten mevcut."
fi

envsubst '${DOMAIN_NAME}' < /etc/nginx/nginx.conf.template > /etc/nginx/nginx.conf

echo "[i] NGINX başlatılıyor..."

exec nginx -g 'daemon off;'
