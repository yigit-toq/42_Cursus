/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:13:36 by ytop              #+#    #+#             */
/*   Updated: 2024/06/11 17:21:32 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define END	"\033[0m"

# define WIN_NAME	"Minerman! Pro"

# define CONST		64

# define F_SPEED	2

# define PLAYER_SPEED	32
# define ENEMY_SPEED	8

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53
# define KEY_SPACE	49

# define WALL		'1'
# define FLOOR		'0'
# define PLAYER		'P'
# define COLLECT	'C'
# define EXIT		'E'

# define FRONT		'F'
# define BACK		'B'
# define LEFT		'L'
# define RIGHT		'R'

# define VISITED	'V'

# define ENEMY		'A'

# define PLAYER_COUNT	1
# define EXIT_COUNT		1

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

# define FLOOR_IMG			"./textures/0-environment/"
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
	void	*img[4];
	int		frame;
	int		unlock;
}			t_door;

typedef struct key
{
	void	*img[9];
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
	int		collect;
	int		player;
	int		enemy;
	int		score;
	int		floor;
	int		wall;
	int		exit;
	int		step;
	int		v_obj[3];
	int		e_dir[2];
}			t_count;

typedef struct player
{
	void	*img;
	void	*img_die[5];
	void	*img_f[3];
	void	*img_b[3];
	void	*img_l[3];
	void	*img_r[3];
	int		death;
	int		frame;
	int		x;
	int		y;
	int		t_x;
	int		t_y;
	char	direction;
}			t_player;

typedef struct img
{
	void	*explosion[6];
	void	*dynamite[9];
	void	*enemy_f[3];
	void	*enemy_b[3];
	void	*enemy_l[3];
	void	*enemy_r[3];
	void	*floor[3];
	void	*collect;
	void	*wall;
	void	*exit;
	int		w;
	int		h;
}			t_img;

typedef struct game
{
	t_dynamite	*dynamite;
	t_player	*player;
	t_count		*count;
	t_door		*door;
	t_map		*map;
	t_img		*img;
	t_key		*key;
	t_enemy		**enemy;
	void		*mlx;
	void		*win;
}			t_game;

void	floor_init(t_game *game, int x, int y, int i);

void	enemy_init(t_game *game);

void	enemy_controller(t_game *game, t_enemy **enemy);

void	enemy_finder(t_enemy **enemy, t_game *game, int x, int y);

char	enemy_direction(t_game *game, t_enemy *enemy, int x, int y);

void	enemy_animation(t_game *game, t_enemy *enemy);

void	dynamite_animation(t_game *game);
void	collect_animation(t_game *game);
void	door_animation(t_game *game);

void	dynamite_drop(t_game *game);

int		player_front_animation(t_game *game, int x, int y);
int		player_back_animation(t_game *game, int x, int y);

int		player_right_animation(t_game *game, int x, int y);
int		player_left_animation(t_game *game, int x, int y);

void	put_object(t_game *game, int x, int y, void *img);

void	*new_image(t_game *game, char *path, char *string);

void	draw_map(t_game *game);

void	add_image(t_game *game);

void	object_control(t_game *game);

void	wall_control(t_map *map, int x, int y, char **path);
void	char_control(t_map *map, int x, int y, char **path);

void	path_finder(t_count *count, char **map, int x, int y);

void	map_reading(t_game *game, char *map, char *total_line);

void	extension_controller(char *path);

void	array_free(void **ptr, int length);

int		key_controller(int keycode, t_game *game);
int		close_controller(t_game *game);

int		static_position(int keycode, t_game *game);

void	error_controller(t_game *game, char type, char *message, void *ptr);
#endif
