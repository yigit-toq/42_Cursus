# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 10:36:40 by ytop              #+#    #+#              #
#    Updated: 2025/11/22 18:20:28 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CMP_FILE		=	srcs/docker-compose.yml
ENV_FILE		=	srcs/.env

DATA_PATH		=	$(HOME)/data

all				:	dirs build up

dirs			:
					@sudo mkdir -p $(DATA_PATH)/db_data
					@sudo mkdir -p $(DATA_PATH)/wp_data

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
					@sudo rm -rf /home/ytop/data/db_data
					@sudo rm -rf /home/ytop/data/wp_data

nginx			:
					@docker exec -it nginx sh

mariadb			:
					@docker exec -it mariadb sh

wordpress		:
					@docker exec -it wordpress sh

nginx_logs		:
					@docker logs -f nginx

mariadb_logs	:
					@docker logs -f mariadb

wordpress_logs	:
					@docker logs -f wordpress

.PHONY			:	all dirs build up down clean fclean nginx nginx_logs mariadb mariadb_logs wordpress wordpress_logs
