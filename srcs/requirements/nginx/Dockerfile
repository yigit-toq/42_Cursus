FROM	alpine:3.21

# NGINX, OpenSSL (sertifika için) ve gettext (envsubst komutu için) kur
RUN		apk update && apk add --no-cache	\
		nginx								\
		openssl								\
		gettext

COPY	./conf/nginx.conf.template /etc/nginx/nginx.conf.template

COPY	./tools/setup.sh /usr/local/bin/setup.sh

RUN		chmod +x /usr/local/bin/setup.sh

# Projenin tek giriş portu olan 443'ü (HTTPS) açığa çıkar
EXPOSE	443

# Konteyner çalıştığında setup.sh betiğimizi çalıştır
ENTRYPOINT ["/usr/local/bin/setup.sh"]
