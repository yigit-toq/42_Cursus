FROM	alpine:3.18

# WordPress'in MariaDB'ye bağlanması için 'php-mysqli' şarttır.
RUN		apk update && apk add --no-cache \
		php82 \
		php82-fpm \
		php82-mysqli \
		php82-json \
		php82-curl \
		php82-dom \
		php82-exif \
		php82-fileinfo \
		php82-mbstring \
		php82-openssl \
		php82-phar \
		php82-xml \
		php82-zip \
		mariadb-client

# 'php' komutunun 'php82'yi göstermesi için sembolik link oluştur
RUN		ln -s /usr/bin/php82 /usr/bin/php

# PHP-FPM'in konteyner dışından (NGINX'ten) gelen bağlantıları dinlemesi
# için konfigürasyon dosyamızı kopyala
COPY	./conf/www.conf /etc/php82/php-fpm.d/www.conf

# WordPress'i indirip kuracak olan
# giriş betiğimizi (entrypoint script) kopyala
COPY	./tools/setup.sh /usr/local/bin/setup.sh
RUN		chmod +x /usr/local/bin/setup.sh

# PHP-FPM'in varsayılan portunu açığa çıkar
# (Bu port sadece Docker ağı içinde NGINX tarafından erişilebilir olacak)
EXPOSE	9000

# Konteyner çalıştığında setup.sh betiğimizi çalıştır
ENTRYPOINT ["/usr/local/bin/setup.sh"]
