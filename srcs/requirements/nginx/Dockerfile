FROM	alpine:3.21

RUN		apk update && apk add --no-cache	\
		nginx								\
		openssl								\
		gettext

COPY	./conf/nginx.conf.template /etc/nginx/nginx.conf.template

COPY	./tools/setup.sh /usr/local/bin/setup.sh

RUN		chmod +x /usr/local/bin/setup.sh

EXPOSE	443

ENTRYPOINT ["/usr/local/bin/setup.sh"]
