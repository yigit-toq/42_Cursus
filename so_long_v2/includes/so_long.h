/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:13:36 by ytop              #+#    #+#             */
/*   Updated: 2024/06/07 14:58:56 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define END	"\033[0m"

# define WIN_NAME	"Minerman! Classic"

# define CONST		64

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53

# define WALL		'1'
# define FLOOR		'0'
# define PLAYER		'P'
# define COLLECT	'C'
# define EXIT		'E'

# define VISITED	'V'

# define PLAYER_COUNT	1
# define EXIT_COUNT		1

# define DOOR_IMG			"./textures/6-door/0.xpm"

# define PLAYER_IMG			"./textures/5-player/f/0.xpm"

# define COLLECTABLE_IMG	"./textures/1-collectable/1.xpm"

# define FLOOR_IMG			"./textures/0-environment/0.xpm"
# define WALL_IMG			"./textures/0-environment/wall.xpm"

typedef struct map
{
	char	**map;
	int		w;
	int		h;
}			t_map;

typedef struct count
{
	int		collect;
	int		player;
	int		floor;
	int		wall;
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
	void	*collect;
	void	*floor;
	void	*wall;
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

void	object_control(t_game *game);

void	wall_control(t_map *map, int x, int y, char **path);
void	char_control(t_map *map, int x, int y, char **path);

void	path_finder(t_count *count, char **map, int x, int y);

void	map_reading(t_game *game, char *map, char *total_line);

void	extension_controller(char *path);

void	map_free(char **map, int length);

int		key_controller(int keycode, t_game *game);
int		close_controller(t_game *game);

void	error_controller(t_game *game, char type, char *message, void *ptr);
#endif
