# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 10:36:40 by ytop              #+#    #+#              #
#    Updated: 2025/11/02 10:38:23 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CMP_FILE = srcs/docker-compose.yml
ENV_FILE = srcs/.env

all				:	build up

build			:
					@docker compose -f $(CMP_FILE) --env-file $(ENV_FILE) build --no-cache

up				:
					@docker compose -f $(CMP_FILE) --env-file $(ENV_FILE) up -d

down			:
					@docker compose -f $(CMP_FILE) --env-file $(ENV_FILE) down

clean			:
					@docker compose -f $(CMP_FILE) --env-file $(ENV_FILE) down -v

fclean			:	clean
					@docker system prune -af

nginx			:
					@docker exec -it nginx bash

mariadb			:
					@docker exec -it mariadb bash

wordpress		:
					@docker exec -it wordpress bash

nginx_logs		:
					@docker logs -f nginx

mariadb_logs	:
					@docker logs -f mariadb

wordpress_logs	:
					@docker logs -f wordpress

.PHONY			:	all build up down clean fclean nginx nginx_logs mariadb mariadb_logs wordpress wordpress_logs
