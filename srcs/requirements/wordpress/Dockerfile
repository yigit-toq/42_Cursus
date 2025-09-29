FROM debian:stable-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends php-fpm php-cli php-mysql php-gd php-xml php-mbstring wget unzip zip ca-certificates procps \
    && rm -rf /var/lib/apt/lists/*

# Create web root
RUN mkdir -p /var/www/html && chown -R www-data:www-data /var/www/html

# Install wp-cli for convenience (optional)
RUN wget -q https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -O /usr/local/bin/wp && \
    chmod +x /usr/local/bin/wp

COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

WORKDIR /var/www/html

VOLUME ["/var/www/html"]

EXPOSE 9000

# We run php-fpm in the foreground (no hacks)
CMD ["php-fpm7.4", "-F"]
