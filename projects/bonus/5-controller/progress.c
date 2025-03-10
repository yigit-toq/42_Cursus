/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:35:40 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:41:34 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	add_slot(t_slot *slot, int curr, t_anim *anim, int loop)
{
	static int	index;

	slot->index = index++;
	if (anim[TAKE].frame)
		slot->take = &anim[TAKE];
	if (anim[IDLE].frame)
		slot->idle = &anim[IDLE];
	if (anim[FIRE].frame)
		slot->fire = &anim[FIRE];
	if (anim[SKIN].frame)
		slot->skin = &anim[SKIN];
	slot->curr = &anim[curr];
	slot->curr->loop = loop;
}

// anim[0] = take, anim[1] = idle, anim[2] = skin, anim[3] = fire

void	init_slot(void)
{
	t_game	*game;
	t_img	*img;

	game = get_game();
	img = game->img;
	init_animation(&img->knife[TAKE], (t_size){0, 15}, DELAY, KNIFE_TAKE);
	init_animation(&img->knife[IDLE], (t_size){0, 10}, DELAY, KNIFE_IDLE);
	add_slot(&game->player.slots[0], 1, img->knife, TRUE);
	init_animation(&img->vandal[TAKE], (t_size){0, 15}, DELAY, VANDAL_TAKE);
	init_animation(&img->vandal[IDLE], (t_size){0, 20}, DELAY, VANDAL_IDLE);
	init_animation(&img->vandal[FIRE], (t_size){0, 04}, DELAY, VANDAL_FIRE);
	init_animation(&img->vandal[SKIN], (t_size){0, 80}, DELAY, VANDAL_SKIN);
	add_slot(&game->player.slots[1], 1, img->vandal, TRUE);
	init_animation(&img->qskill[TAKE], (t_size){0, 07}, DELAY, QSKILL_TAKE);
	init_animation(&img->qskill[IDLE], (t_size){0, 35}, DELAY, QSKILL_IDLE);
	init_animation(&img->qskill[FIRE], (t_size){0, 05}, DELAY, QSKILL_FIRE);
	add_slot(&game->player.slots[2], 1, img->qskill, TRUE);
	init_animation(&img->rskill[FIRE], (t_size){2, 10}, DELAY, RSKILL_FIRE);
	add_slot(&game->player.slots[3], 3, img->rskill, FALSE);
	game->player.slots[1].gun = init_gun(120, 10, 10);
	game->player.slots[2].gun = init_gun(001, 10, 00);
	game->player.slot = &game->player.slots[0];
	game->player.slot->curr->play = TRUE;
}

static void	init_door(t_size index);
static void	init_enmy(t_size index);

void	init_objs(void)
{
	t_game	*game;
	t_size	index;

	ft_bzero(&index, sizeof(t_size));
	game = get_game();
	game->grp->door = ft_calloc(game->count.door, sizeof(t_door));
	error_controller("Failed to allocate memory.", game->grp->door);
	game->grp->enmy = ft_calloc(game->count.enmy, sizeof(t_enmy));
	error_controller("Failed to allocate memory.", game->grp->enmy);
	while (game->map->map[index.y])
	{
		index.x = 0;
		while (game->map->map[index.y][index.x])
		{
			init_door(index);
			init_enmy(index);
			index.x++;
		}
		index.y++;
	}
}

static void	init_door(t_size index)
{
	t_game	*game;

	game = get_game();
	if (game->map->map[index.y][index.x] == DOOR)
	{
		game->grp->door[game->grp->d_i].coor.x = index.x;
		game->grp->door[game->grp->d_i].coor.y = index.y;
		if (game->grp->d_i % 2)
		{
			game->grp->door[game->grp->d_i].filter = 0x980088;
			init_animation(&game->grp->door[game->grp->d_i].anim,
				(t_size){0, 64}, DELAY / 2, DOOR1_PATH);
		}
		else
		{
			game->grp->door[game->grp->d_i].filter = 0xFF000000;
			init_animation(&game->grp->door[game->grp->d_i].anim,
				(t_size){0, 9}, DELAY / 2, DOOR2_PATH);
		}
		game->grp->d_i++;
	}
}

static void	init_enmy(t_size index)
{
	t_game	*game;

	game = get_game();
	if (game->map->map[index.y][index.x] == ENMY)
	{
		game->grp->enmy[game->grp->e_i].pos.x = index.x;
		game->grp->enmy[game->grp->e_i].pos.y = index.y;
		init_animation(&game->grp->enmy[game->grp->e_i].anim,
			(t_size){0, 6}, DELAY / 2, ENMY_PATH);
		game->grp->e_i++;
	}
}
