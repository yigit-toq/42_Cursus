#!/bin/sh
set -e

# 1. SSL sertifikası için klasör oluştur
mkdir -p /etc/nginx/ssl

# 2. SSL sertifikasının zaten var olup olmadığını kontrol et
if [ ! -f /etc/nginx/ssl/nginx.crt ]; then
	echo "[i] NGINX: Kendi imzaladığımız SSL sertifikası oluşturuluyor..."
	
	# Proje gereksinimlerine göre .env dosyasından alınan $DOMAIN_NAME
	# ile bir sertifika oluştur
	openssl req -x509 -nodes -days 365 -newkey rsa:2048	\
		-keyout /etc/nginx/ssl/nginx.key				\
		-out /etc/nginx/ssl/nginx.crt					\
		-subj "/C=TR/ST=Kocaeli/L=Gebze/O=42School/CN=$DOMAIN_NAME"
else
	echo "[i] NGINX: SSL sertifikası zaten mevcut."
fi

# 3. 'nginx.conf.template' dosyasını al, $DOMAIN_NAME değişkenini
#    çevre değişkeninden (environment) gelen değerle değiştir ve
#    son konfigürasyon dosyasını oluştur.
envsubst '${DOMAIN_NAME}' < /etc/nginx/nginx.conf.template > /etc/nginx/nginx.conf

# 4. NGINX sunucusunu ön planda çalıştır
# 'daemon off;' NGINX'in arka plana geçmesini engeller
# ve konteynerin çalışır kalmasını sağlar
echo "[i] NGINX başlatılıyor..."
exec nginx -g 'daemon off;'
