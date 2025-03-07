/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mandatory.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 16:59:04 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MANDATORY_H
# define CUB3D_MANDATORY_H

# include "./utils/libft.h"

# include "./other/mandatory/struct.h"

/*------------------------------------------------------------*/

t_game			*get_game(void);

int				exit_game(t_game *game);

/*----------------------ERROR CONTROLLER----------------------*/

void			exten_controller(char *path);

void			error_controller(char *message, void *pointer);

/*----------------------INPUT CONTROLLER----------------------*/

int				update_position(void);

int				key_press_handler(int key, t_game *game);

int				key_release_handler(int key, t_game *game);

/*----------------------COLOR CONTROLLER----------------------*/

unsigned int	rgb_to_hexa(int r, int g, int b);

unsigned int	pixel_color(t_data img, int x, int y);

void			mlx_image_put(t_data img, int x, int y, unsigned int color);

/*----------------------FILE  CONTROLLER----------------------*/

int				path_control(void);

void			files_controller(char *path);

/*----------------------INIT  CONTROLLER----------------------*/

void			init_game(void);

/*----------------------MATH  CONTROLLER----------------------*/

double			deg_to_rad(double degree);
double			rad_to_deg(double radian);

double			grid_to_ct(double pos, double scale);

/*----------------------UTIL  CONTROLLER----------------------*/

t_data			add_image(char *path, t_size size);

int				open_file(char *path);

int				wtspace_check(char c);

char			*wtspace_trim(char *str);

/*------------------------------------------------------------*/

void			render_frame(t_ray *ray, int x);

/*------------------------------------------------------------*/

char			**copy_array(char **array, int size);

/*------------------------------------------------------------*/

int				raycast(void);

/*------------------------------------------------------------*/
#endif
