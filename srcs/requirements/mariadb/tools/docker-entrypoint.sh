#!/bin/sh
set -e

# This entrypoint initializes MariaDB data directory if empty and creates the database and user.
# Passwords are read from docker secrets (files).
MYSQL_ROOT_PASSWORD_FILE=/run/secrets/mysql_root_password
MYSQL_PASSWORD_FILE=/run/secrets/mysql_password

if [ ! -d /var/lib/mysql/mysql ]; then
    echo "Initializing MariaDB data directory..."
    mysqld --initialize-insecure --user=mysql --datadir=/var/lib/mysql
    chown -R mysql:mysql /var/lib/mysql

    # Start temporary server
    mysqld_safe --skip-networking &

    # Wait for server socket
    i=0
    until mysqladmin ping >/dev/null 2>&1; do
        sleep 0.5
        i=$((i+1))
        if [ $i -gt 60 ]; then
            echo "MariaDB did not start in time" >&2
            exit 1
        fi
    done

    ROOT_PWD=""
    if [ -f "$MYSQL_ROOT_PASSWORD_FILE" ]; then
        ROOT_PWD=$(cat "$MYSQL_ROOT_PASSWORD_FILE")
    fi

    USER_PWD=""
    if [ -f "$MYSQL_PASSWORD_FILE" ]; then
        USER_PWD=$(cat "$MYSQL_PASSWORD_FILE")
    fi

    # Secure installation and create DB + user
    mysql <<-EOSQL
        ALTER USER 'root'@'localhost' IDENTIFIED BY '${ROOT_PWD}';
        DELETE FROM mysql.user WHERE User='';
        DROP DATABASE IF EXISTS test;
        CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE:-wordpress} DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
        CREATE USER IF NOT EXISTS '${MYSQL_USER:-wp_user}'@'%' IDENTIFIED BY '${USER_PWD}';
        GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE:-wordpress}.* TO '${MYSQL_USER:-wp_user}'@'%';
        FLUSH PRIVILEGES;
EOSQL

    # Shutdown temporary server
    mysqladmin shutdown
    echo "MariaDB initialization complete."
fi

exec "$@"
