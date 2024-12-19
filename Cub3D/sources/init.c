/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/12/17 16:20:08 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	raycast();
	mlx_put_image_to_window(game->mlx, game->win, game->img->frame.img, 0, 0);
	minimap_loop();
	return (SUCCESS);
}

static void	init_img(void)
{
	t_img	*img;
	t_map	*map;
	t_size	size;
	int		i;

	img	= get_game()->img;
	map = get_game()->map;
	size.x = WIN_W;
	size.y = WIN_H;
	i = 0;
	while (i < MAX_PATH)
	{
		if (!img->dir_symbl[i].img)
			error_controller("Texture path is not found.", NULL);
		img->dir_symbl[i] = add_image(img->dir_symbl[i].img, (t_size){0, 0});
		i++;
	}
	img->frame = add_image(NULL, size);
	size.x = map->scale.x * map->size.x;
	size.y = map->scale.y * map->size.y;
	img->minimap = add_image(NULL, size);
	img->hex_color[0] = rgb_to_hex(img->rgb_color[0][0], img->rgb_color[0][1], img->rgb_color[0][2]);
	img->hex_color[1] = rgb_to_hex(img->rgb_color[1][0], img->rgb_color[1][1], img->rgb_color[1][2]);

	img->cross = add_image("../Frame/output64.xpm", (t_size){0, 0});

	img->gun_frame[0] = add_image("../Frame/Reaver/xpm/output_001.xpm", (t_size){0, 0});
	img->gun_frame[1] = add_image("../Frame/Reaver/xpm/output_002.xpm", (t_size){0, 0});
	img->gun_frame[2] = add_image("../Frame/Reaver/xpm/output_003.xpm", (t_size){0, 0});
	img->gun_frame[3] = add_image("../Frame/Reaver/xpm/output_004.xpm", (t_size){0, 0});
	img->gun_frame[4] = add_image("../Frame/Reaver/xpm/output_005.xpm", (t_size){0, 0});
	img->gun_frame[5] = add_image("../Frame/Reaver/xpm/output_006.xpm", (t_size){0, 0});
	img->gun_frame[6] = add_image("../Frame/Reaver/xpm/output_007.xpm", (t_size){0, 0});
	img->gun_frame[7] = add_image("../Frame/Reaver/xpm/output_008.xpm", (t_size){0, 0});
	img->gun_frame[8] = add_image("../Frame/Reaver/xpm/output_009.xpm", (t_size){0, 0});
	img->gun_frame[9] = add_image("../Frame/Reaver/xpm/output_010.xpm", (t_size){0, 0});
	img->gun_frame[10] = add_image("../Frame/Reaver/xpm/output_011.xpm", (t_size){0, 0});
	img->gun_frame[11] = add_image("../Frame/Reaver/xpm/output_012.xpm", (t_size){0, 0});
	img->gun_frame[12] = add_image("../Frame/Reaver/xpm/output_013.xpm", (t_size){0, 0});
	img->gun_frame[13] = add_image("../Frame/Reaver/xpm/output_014.xpm", (t_size){0, 0});
	img->gun_frame[14] = add_image("../Frame/Reaver/xpm/output_015.xpm", (t_size){0, 0});
	img->gun_frame[15] = add_image("../Frame/Reaver/xpm/output_016.xpm", (t_size){0, 0});
	img->gun_frame[16] = add_image("../Frame/Reaver/xpm/output_017.xpm", (t_size){0, 0});
	img->gun_frame[17] = add_image("../Frame/Reaver/xpm/output_018.xpm", (t_size){0, 0});
	img->gun_frame[18] = add_image("../Frame/Reaver/xpm/output_019.xpm", (t_size){0, 0});
	img->gun_frame[19] = add_image("../Frame/Reaver/xpm/output_020.xpm", (t_size){0, 0});
	img->gun_frame[20] = add_image("../Frame/Reaver/xpm/output_021.xpm", (t_size){0, 0});
	img->gun_frame[21] = add_image("../Frame/Reaver/xpm/output_022.xpm", (t_size){0, 0});
	img->gun_frame[22] = add_image("../Frame/Reaver/xpm/output_023.xpm", (t_size){0, 0});
	img->gun_frame[23] = add_image("../Frame/Reaver/xpm/output_024.xpm", (t_size){0, 0});
	img->gun_frame[24] = add_image("../Frame/Reaver/xpm/output_025.xpm", (t_size){0, 0});
	img->gun_frame[25] = add_image("../Frame/Reaver/xpm/output_026.xpm", (t_size){0, 0});
	img->gun_frame[26] = add_image("../Frame/Reaver/xpm/output_027.xpm", (t_size){0, 0});
	img->gun_frame[27] = add_image("../Frame/Reaver/xpm/output_028.xpm", (t_size){0, 0});
	img->gun_frame[28] = add_image("../Frame/Reaver/xpm/output_029.xpm", (t_size){0, 0});
	img->gun_frame[29] = add_image("../Frame/Reaver/xpm/output_030.xpm", (t_size){0, 0});
	img->gun_frame[30] = add_image("../Frame/Reaver/xpm/output_031.xpm", (t_size){0, 0});
	img->gun_frame[31] = add_image("../Frame/Reaver/xpm/output_032.xpm", (t_size){0, 0});
	img->gun_frame[32] = add_image("../Frame/Reaver/xpm/output_033.xpm", (t_size){0, 0});
	img->gun_frame[33] = add_image("../Frame/Reaver/xpm/output_034.xpm", (t_size){0, 0});
	img->gun_frame[34] = add_image("../Frame/Reaver/xpm/output_035.xpm", (t_size){0, 0});
	img->gun_frame[35] = add_image("../Frame/Reaver/xpm/output_036.xpm", (t_size){0, 0});
	img->gun_frame[36] = add_image("../Frame/Reaver/xpm/output_037.xpm", (t_size){0, 0});
	img->gun_frame[37] = add_image("../Frame/Reaver/xpm/output_038.xpm", (t_size){0, 0});
	img->gun_frame[38] = add_image("../Frame/Reaver/xpm/output_039.xpm", (t_size){0, 0});
	img->gun_frame[39] = add_image("../Frame/Reaver/xpm/output_040.xpm", (t_size){0, 0});
	img->gun_frame[40] = add_image("../Frame/Reaver/xpm/output_041.xpm", (t_size){0, 0});
	img->gun_frame[41] = add_image("../Frame/Reaver/xpm/output_042.xpm", (t_size){0, 0});
	img->gun_frame[42] = add_image("../Frame/Reaver/xpm/output_043.xpm", (t_size){0, 0});
	img->gun_frame[43] = add_image("../Frame/Reaver/xpm/output_044.xpm", (t_size){0, 0});
	img->gun_frame[44] = add_image("../Frame/Reaver/xpm/output_045.xpm", (t_size){0, 0});
	img->gun_frame[45] = add_image("../Frame/Reaver/xpm/output_046.xpm", (t_size){0, 0});
	img->gun_frame[46] = add_image("../Frame/Reaver/xpm/output_047.xpm", (t_size){0, 0});
	img->gun_frame[47] = add_image("../Frame/Reaver/xpm/output_048.xpm", (t_size){0, 0});
	img->gun_frame[48] = add_image("../Frame/Reaver/xpm/output_049.xpm", (t_size){0, 0});
	img->gun_frame[49] = add_image("../Frame/Reaver/xpm/output_050.xpm", (t_size){0, 0});
	img->gun_frame[50] = add_image("../Frame/Reaver/xpm/output_051.xpm", (t_size){0, 0});
	img->gun_frame[51] = add_image("../Frame/Reaver/xpm/output_052.xpm", (t_size){0, 0});
	img->gun_frame[52] = add_image("../Frame/Reaver/xpm/output_053.xpm", (t_size){0, 0});
	img->gun_frame[53] = add_image("../Frame/Reaver/xpm/output_054.xpm", (t_size){0, 0});
	img->gun_frame[54] = add_image("../Frame/Reaver/xpm/output_055.xpm", (t_size){0, 0});
	img->gun_frame[55] = add_image("../Frame/Reaver/xpm/output_056.xpm", (t_size){0, 0});
	img->gun_frame[56] = add_image("../Frame/Reaver/xpm/output_057.xpm", (t_size){0, 0});
	img->gun_frame[57] = add_image("../Frame/Reaver/xpm/output_058.xpm", (t_size){0, 0});
	img->gun_frame[58] = add_image("../Frame/Reaver/xpm/output_059.xpm", (t_size){0, 0});
	img->gun_frame[59] = add_image("../Frame/Reaver/xpm/output_060.xpm", (t_size){0, 0});
	img->gun_frame[60] = add_image("../Frame/Reaver/xpm/output_061.xpm", (t_size){0, 0});
	img->gun_frame[61] = add_image("../Frame/Reaver/xpm/output_062.xpm", (t_size){0, 0});
	img->gun_frame[62] = add_image("../Frame/Reaver/xpm/output_063.xpm", (t_size){0, 0});
	img->gun_frame[63] = add_image("../Frame/Reaver/xpm/output_064.xpm", (t_size){0, 0});
	img->gun_frame[64] = add_image("../Frame/Reaver/xpm/output_065.xpm", (t_size){0, 0});
	img->gun_frame[65] = add_image("../Frame/Reaver/xpm/output_066.xpm", (t_size){0, 0});
	img->gun_frame[66] = add_image("../Frame/Reaver/xpm/output_067.xpm", (t_size){0, 0});
	img->gun_frame[67] = add_image("../Frame/Reaver/xpm/output_068.xpm", (t_size){0, 0});
	img->gun_frame[68] = add_image("../Frame/Reaver/xpm/output_069.xpm", (t_size){0, 0});
	img->gun_frame[69] = add_image("../Frame/Reaver/xpm/output_070.xpm", (t_size){0, 0});
	img->gun_frame[70] = add_image("../Frame/Reaver/xpm/output_071.xpm", (t_size){0, 0});
	img->gun_frame[71] = add_image("../Frame/Reaver/xpm/output_072.xpm", (t_size){0, 0});
	img->gun_frame[72] = add_image("../Frame/Reaver/xpm/output_073.xpm", (t_size){0, 0});
	img->gun_frame[73] = add_image("../Frame/Reaver/xpm/output_074.xpm", (t_size){0, 0});
	img->gun_frame[74] = add_image("../Frame/Reaver/xpm/output_075.xpm", (t_size){0, 0});
}

void	init_game(void)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, NAME);
	init_img();
	mlx_loop_hook(game->mlx, render_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_loop(game->mlx);
}
