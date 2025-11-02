FROM	alpine:3.18

RUN		apk update && apk add --no-cache	\
		mariadb								\
		mariadb-client

# MariaDB'nin diğer konteynerlerden gelen bağlantıları
# kabul etmesi için konfigürasyon dosyamızı kopyala
COPY	./conf/my.cnf /etc/my.cnf.d/my.cnf

RUN		chmod 644 /etc/my.cnf.d/my.cnf

# Veritabanını ilk çalışmada kuracak olan
# giriş betiğimizi (entrypoint script) kopyala
COPY	./tools/setup.sh /usr/local/bin/setup.sh

# Betiği çalıştırılabilir yap
RUN		chmod +x /usr/local/bin/setup.sh

# MariaDB'nin varsayılan portunu açığa çıkar
# (Bu port sadece Docker ağı içinde erişilebilir olacak)
EXPOSE	3306

# Konteyner çalıştığında setup.sh betiğimizi çalıştır
# Bu betik, MariaDB sunucusunu PID 1 olarak çalıştıracak
ENTRYPOINT ["/usr/local/bin/setup.sh"]
