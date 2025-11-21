FROM	alpine:3.21

# WordPress'in MariaDB'ye bağlanması için 'php-mysqli' şarttır.

RUN		apt-get update && apt-get install -y php php-mysqli php-fpm php-cli wget curl tar mariadb-client

# RUN		apk update && apk add --no-cache	\
# 		php82								\
# 		php82-fpm							\
# 		php82-mysqli						\
# 		php82-json							\
# 		php82-curl							\
# 		php82-dom							\
# 		php82-exif							\
# 		php82-fileinfo						\
# 		php82-mbstring						\
# 		php82-openssl						\
# 		php82-phar							\
# 		php82-xml							\
# 		php82-zip							\
# 		mariadb-client

# 'php' komutunun 'php82'yi göstermesi için sembolik link oluştur
RUN		ln -s /usr/bin/php82 /usr/bin/php

COPY	./conf/www.conf /etc/php82/php-fpm.d/www.conf

COPY	./tools/setup.sh /usr/local/bin/setup.sh

RUN		chmod +x /usr/local/bin/setup.sh

EXPOSE	9000

ENTRYPOINT ["/usr/local/bin/setup.sh"]
