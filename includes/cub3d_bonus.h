/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:29:56 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 16:59:09 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "./utils/libft.h"

# include "./other/bonus/struct.h"

/*------------------------------------------------------------*/

t_game			*get_game(void);

int				exit_game(t_game *game, int status);

/*----------------------ERROR CONTROLLER----------------------*/

void			exten_controller(char *path);

void			error_controller(char *message, void *pointer);

/*----------------------INPUT CONTROLLER----------------------*/

int				update_position(void);

int				key_press_handler(int key, t_game *game);

int				key_relse_handler(int key, t_game *game);

int				mouse_moves_handler(int x, int y);

int				mouse_press_handler(int button, int x, int y);

int				mouse_relse_handler(int button, int x, int y);

/*----------------------COLOR CONTROLLER----------------------*/

unsigned int	rgb_to_hexa(int r, int g, int b);

unsigned int	pixel_color(t_data img, int x, int y);

void			mlx_image_put(t_data img, int x, int y, unsigned int color);

/*----------------------FILE  CONTROLLER----------------------*/

void			path_control(void);

void			files_controller(char *path);

/*----------------------INIT  CONTROLLER----------------------*/

void			init_game(void);

/*----------------------MATH  CONTROLLER----------------------*/

t_size			tc_size(t_vect vect);
t_vect			tc_vect(t_size size);

double			deg_to_rad(double degree);
double			rad_to_deg(double radian);

double			grid_to_ct(double pos, double scale);

/*----------------------UTIL  CONTROLLER----------------------*/

t_data			add_image(char *path, t_size size);

int				open_file(char *path);

/*------------------------------------------------------------*/

int				wtspace_check(char c);

char			*wtspace_trim(char *str);

/*----------------------ANIM  CONTROLLER----------------------*/

void			input_animation(int key);

void			updt_animation(t_anim *anim, int reverse);

void			swap_animation(t_anim *anim, t_anim *new);

void			init_animation(t_anim *anim, t_size range, int delay, char *path);

/*----------------------DRAW  CONTROLLER----------------------*/

void			draw_rect(t_data data, t_vect center, t_vect size, int color);

int				draw_circ(t_data data, t_vect center, t_vect radius, int color);

/*------------------------------------------------------------*/

void			render_frame(t_ray *ray, int x, double angle);

int				image_filter(int index, int color, char filter, int limit);

/*------------------------------------------------------------*/

char			**copy_array(char **array, int size);

/*------------------------------------------------------------*/

int				raycast(void);

void			minimap(void);

/*------------------------------------------------------------*/

void			init_slot(void);

/*------------------------------------------------------------*/

void			get_load(void);

char			*get_fps(char *fps);

/*------------------------------------------------------------*/
#endif
