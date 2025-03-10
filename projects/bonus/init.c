/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:39:21 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

#include <mlx.h>

static void	update_animtion(void)
{
	t_game	*game;

	game = get_game();
	if (game->player.slot->fire && game->player.attack)
	{
		if (game->player.slot->gun->ammo > 0)
		{
			if (game->player.slot->gun)
			{
				game->player.slot->gun->reload = 0;
				game->player.slot->gun->ammo--;
			}
			game->player.slot->curr->play = FALSE;
			game->img->next_anim = game->player.slot->fire;
		}
	}
	if (game->grp->curr && game->grp->curr->anim.play == TRUE)
	{
		if (game->grp->curr->state == FALSE)
			updt_animation(&game->grp->curr->anim, FALSE);
		else
			updt_animation(&game->grp->curr->anim, TRUE);
	}
}

//game->curr->ratio = (double)game->curr->anim.index
// /(double)game->curr->anim.total;

// void	update_enemy(void)
// {
// 	t_game	*game;
// 	t_vect	d;
// 	t_vect	p;
// 	int		i;
//
// 	i = 0;
// 	game = get_game();
// 	while (i < game->count.enmy)
// 	{
// 		d.x = game->grp->enmy[i].pos.x - game->player.pos.x;
// 		d.y = game->grp->enmy[i].pos.y - game->player.pos.y;
// 		p = (t_vect){cos(game->player.theta), sin(game->player.theta)};
// 		if (vector_angle(p, d) < 0.5f)
// 		{
// 			game->grp->enmy[i].dist = sqrt(d.x * d.x + d.y * d.y);
// 			game->grp->enmy[i].visible = TRUE;
// 		}
// 		else
// 		{
// 			game->grp->enmy[i].visible = FALSE;
// 		}
// 		i++;
// 	}
// }

static int	next_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	update_animtion();
	swap_animation(game->player.slot->curr, game->img->next_anim);
	mlx_put_image_to_window(game->mlx, game->win, game->img->bgframe.img, 0, 0);
	mlx_string_put(game->mlx, game->win, 10, 16, 0x000000, get_fps(game->sfps));
	raycast();
	minimap();
	return (SUCCESS);
}

static void	init_img(void)
{
	t_size	size;
	t_img	*img;
	t_map	*map;
	int		len;
	int		i;

	img = get_game()->img;
	map = get_game()->map;
	len = sizeof(img->paths) / sizeof(char *);
	size.x = WIN_W;
	size.y = WIN_H;
	i = 0;
	while (i < DIR)
	{
		img->direct[i] = add_image(img->paths[i], (t_size){0, 0});
		i++;
	}
	img->skybox = add_image(img->paths[len - 3], (t_size){0, 0});
	img->ground = add_image(img->paths[len - 2], (t_size){0, 0});
	img->crossh = add_image(img->paths[len - 1], (t_size){0, 0});
	img->bgframe = add_image(NULL, size);
	size.x = map->mini.x;
	size.y = map->mini.y;
	img->minimap = add_image(NULL, size);
	img->hex[0] = rgb_to_hexa(img->rgb[0][0], img->rgb[0][1], img->rgb[0][2]);
}

void	init_game(void)
{
	t_game		*game;

	game = get_game();
	game->mlx = addgarbage(mlx_init());
	error_controller("Mlx initialization failed", game->mlx);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN);
	error_controller("Window creation failed :D", game->win);
	init_img();
	init_slot();
	init_objs();
	mlx_loop_hook(game->mlx, next_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_relse_handler, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_press_handler, game);
	mlx_hook(game->win, 5, 1L << 3, mouse_relse_handler, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_moves_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_loop(game->mlx);
}
