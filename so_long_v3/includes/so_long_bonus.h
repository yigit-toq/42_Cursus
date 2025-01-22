/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:13:36 by ytop              #+#    #+#             */
/*   Updated: 2025/01/22 14:43:35 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "./utils/macro.h"

# define WIN_NAME			"Minerman! Pro"

# define F_SPEED			3

# define PLAYER_SPEED		8
# define ENEMY_SPEED		8

# define FRONT				'F'
# define BACK				'B'
# define LEFT				'L'
# define RIGHT				'R'

# define ENEMY				'A'

# define DOOR_IMG			"./textures/6-door/"

# define DIE_IMG			"./textures/5-player/0-death/"

# define PLAYER_F_IMG		"./textures/5-player/f/"
# define PLAYER_B_IMG		"./textures/5-player/b/"
# define PLAYER_L_IMG		"./textures/5-player/l/"
# define PLAYER_R_IMG		"./textures/5-player/r/"

# define ENEMY_F_IMG		"./textures/4-enemy/f/"
# define ENEMY_B_IMG		"./textures/4-enemy/b/"
# define ENEMY_L_IMG		"./textures/4-enemy/l/"
# define ENEMY_R_IMG		"./textures/4-enemy/r/"

# define DYNAMITE_IMG		"./textures/3-dynamite/"

# define EXPO_IMG			"./textures/2-explosion/"

# define KEY_IMG			"./textures/1-collectable/"

# define GRND_IMG			"./textures/0-environment/"
# define WALL_IMG			"./textures/0-environment/wall.xpm"

typedef struct enemy
{
	void			*img;
	char			direction;
	int				t_dir[2];
	int				m_dir[2];
	int				frame;
	int				death;
	unsigned int	speed;
}			t_enemy;

typedef struct dynamite
{
	void			*img;
	int				frame;
	int				available;
	int				life_time;
	int				transform[2];
}			t_dynamite;

typedef struct door
{
	t_data	*img[4];
	int		frame;
	int		unlock;
}			t_door;

typedef struct key
{
	t_data	*img[9];
	int		frame;
}			t_key;

typedef struct map
{
	char	**map;
	int		w;
	int		h;
	int		**f_map;
}			t_map;

typedef struct count
{
	int		player;
	int		enemy;
	int		score;
	int		floor;
	int		wall;
	int		coll;
	int		exit;
	int		step;
	int		v_obj[3];
	int		e_dir[2];
}			t_count;

typedef struct player
{
	t_data	*img;
	t_data	*img_die[5];
	t_data	*img_f[3];
	t_data	*img_b[3];
	t_data	*img_l[3];
	t_data	*img_r[3];
	int		death;
	int		frame;
	int		move;
	int		x;
	int		y;
	int		w_t[2];
	int		n_t[2];
	char	direction;
}			t_player;

typedef struct img
{
	t_data	*explosion[6];
	t_data	*dynamite[9];
	t_data	*enemy_f[3];
	t_data	*enemy_b[3];
	t_data	*enemy_l[3];
	t_data	*enemy_r[3];
	t_data	*floor[3];
	t_data	*wall;
	t_data	*coll;
	t_data	*exit;
	int		w;
	int		h;
}			t_img;

typedef struct game
{
	t_dynamite	*dynamite;
	t_player	*player;
	t_count		*count;
	t_door		*door;
	t_key		*keys;
	t_map		*map;
	t_img		*img;
	t_enemy		**enemy;
	void		*mlx;
	void		*win;
}			t_game;

void	floor_init(t_game *game, int x, int y, int i);

void	enemy_init(t_game *game);

void	enemy_animation(t_game *game, t_enemy *enemy);
void	enemy_controller(t_game *game, t_enemy **enemy);

void	enemy_finder(t_game *game, t_enemy **enemy, int x, int y);

char	enemy_direction(t_game *game, t_enemy *enemy, int x, int y);

void	dynamite_drop(t_game *game);

void	door_animation(t_game *game);
void	player_animation(t_game *game);
void	collect_animation(t_game *game);
void	dynamite_animation(t_game *game);

void	*new_image(t_game *game, char *path);

void	put_object(t_game *game, int x, int y, void *img);

void	add_images(t_game *game);

void	draw_level(t_game *game);

void	object_control(t_game *game);

void	wall_control(t_map *map, int x, int y, char **path);
void	char_control(t_map *map, int x, int y, char **path);

void	path_finder(t_count *count, char **map, int x, int y);

void	map_reading(t_game *game, char *map, char *total_line);

void	extension_controller(char *path);

void	array_free(void **ptr, int length);

int		close_controller(t_game *game);

int		key_controller(int keycode, t_game *game);
int		key_up_control(int keycode, t_game *game);

void	error_controller(t_game *game, char type, char *message, void *ptr);
#endif
