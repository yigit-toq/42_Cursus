FROM	alpine:3.18

RUN		apk update && apk add --no-cache	\
		mariadb								\
		mariadb-client

COPY	./conf/my.cnf /etc/my.cnf

RUN		chmod 644 /etc/my.cnf

COPY	./tools/setup.sh /usr/local/bin/setup.sh

RUN		chmod +x /usr/local/bin/setup.sh

# MariaDB'nin varsayılan portunu açığa çıkar
# (Bu port sadece Docker ağı içinde erişilebilir olacak)
EXPOSE	3306

# Konteyner çalıştığında setup.sh betiğimizi çalıştır
# Bu betik, MariaDB sunucusunu PID 1 olarak çalıştıracak
ENTRYPOINT ["/usr/local/bin/setup.sh"]
