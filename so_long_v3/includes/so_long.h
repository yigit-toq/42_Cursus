/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:13:36 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 19:23:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./utils/macro.h"

# define WIN_NAME			"Minerman! Classic"

# define WALL_IMG			"./textures/0-environment/wall.xpm"
# define GRND_IMG			"./textures/0-environment/0.xpm"

# define COLL_IMG			"./textures/1-collectable/1.xpm"

# define DOOR_IMG			"./textures/6-door/0.xpm"

# define PLAYER_IMG			"./textures/5-player/f/0.xpm"

typedef struct map
{
	char	**map;
	int		w;
	int		h;
}			t_map;

typedef struct count
{
	int		player;
	int		floor;
	int		wall;
	int		coll;
	int		exit;
	int		step;
	int		v_obj[2];
	int		e_dir[2];
}			t_count;

typedef struct player
{
	void	*img;
	int		x;
	int		y;
}			t_player;

typedef struct img
{
	void	*floor;
	void	*wall;
	void	*coll;
	void	*exit;
	int		w;
	int		h;
}			t_img;

typedef struct game
{
	t_player	*player;
	t_count		*count;
	t_map		*map;
	t_img		*img;
	void		*mlx;
	void		*win;
}			t_game;

int		draw_map(t_game *game);

void	*new_image(t_game *game, char *path);

void	array_free(char **map, int length);

void	path_finder(t_count *count, char **map, int x, int y);

void	map_reading(t_game *game, char *map, char *total_line);

void	wall_control(t_map *map, int x, int y, char **path);
void	char_control(t_map *map, int x, int y, char **path);

void	object_control(t_game *game);

int		key_controller(int keycode, t_game *game);

int		close_controller(t_game *game);
void	error_controller(t_game *game, char type, char *message, void *ptr);

void	extension_controller(char *path);
#endif
