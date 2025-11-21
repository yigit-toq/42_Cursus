FROM	alpine:3.21

RUN		apk update && apk add --no-cache	\
		mariadb								\
		mariadb-client

COPY	./conf/my.cnf /etc/my.cnf

RUN		chmod 644 /etc/my.cnf

COPY	./tools/setup.sh /usr/local/bin/setup.sh

RUN		chmod +x /usr/local/bin/setup.sh

EXPOSE	3306

ENTRYPOINT ["/usr/local/bin/setup.sh"]
