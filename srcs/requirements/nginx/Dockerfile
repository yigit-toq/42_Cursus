FROM	alpine:3.18

# NGINX, OpenSSL (sertifika için) ve gettext (envsubst komutu için) kur
RUN		apk update && apk add --no-cache \
		nginx \
		openssl \
		gettext

# NGINX konfigürasyonumuzun 'şablonunu' kopyala
# Bu şablon, $DOMAIN_NAME gibi değişkenler içerir
COPY	./conf/nginx.conf.template /etc/nginx/nginx.conf.template

# Konteyner başladığında çalışacak olan
# giriş betiğimizi (entrypoint script) kopyala
COPY	./tools/setup.sh /usr/local/bin/setup.sh
RUN		chmod +x /usr/local/bin/setup.sh

# Projenin tek giriş portu olan 443'ü (HTTPS) açığa çıkar [cite: 70, 77]
EXPOSE	443

# Konteyner çalıştığında setup.sh betiğimizi çalıştır
ENTRYPOINT ["/usr/local/bin/setup.sh"]
