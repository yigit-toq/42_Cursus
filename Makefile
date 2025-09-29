.PHONY: all build up down clean certs

all: build up

build:
	docker-compose -f srcs/docker-compose.yml build --no-cache

up:
	docker-compose -f srcs/docker-compose.yml up -d

down:
	docker-compose -f srcs/docker-compose.yml down

clean:
	docker-compose -f srcs/docker-compose.yml down -v --rmi all --remove-orphans

# Helper: generate self-signed certs for testing (replace with real certs in production)
certs:
	mkdir -p srcs/requirements/nginx/ssl
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	    -keyout srcs/requirements/nginx/ssl/privkey.pem \
	    -out srcs/requirements/nginx/ssl/fullchain.pem \
	    -subj "/CN=$${DOMAIN_NAME}" || true
