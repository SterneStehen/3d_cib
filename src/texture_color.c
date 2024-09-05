/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:50:08 by cpuiu             #+#    #+#             */
/*   Updated: 2024/09/04 23:39:14 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_material_direction_and_wall_hit(t_game *game)
{
	if (game->ray.collision_side == 0 && game->ray.beam_dir_x < 0)
		game->material_data.dir = 0;
	if (game->ray.collision_side == 0 && game->ray.beam_dir_x >= 0)
		game->material_data.dir = 1;
	if (game->ray.collision_side == 1 && game->ray.beam_dir_y < 0)
		game->material_data.dir = 2;
	if (game->ray.collision_side == 1 && game->ray.beam_dir_y >= 0)
		game->material_data.dir = 3;
	if (game->ray.collision_side == 0)
		game->material_data.wall_hit_x = game->ray.pos_y
			+ game->ray.perpwalldist * game->ray.beam_dir_y;
	else
		game->material_data.wall_hit_x = game->ray.pos_x
			+ game->ray.perpwalldist * game->ray.beam_dir_x;
}

static void	draw_wall_pixels(t_game *game)
{
	int	j;

	j = game->ray.begin_draw_px - 1;
	while (++j <= game->ray.finish_draw_px)
	{
		game->material_data.coord_y = (int)game->material_data.position
			& (game->surfaces[game->material_data.dir].win_height
				- 1);
		game->material_data.position += game->material_data.step;
		if (j < game->resolut_height && game->ray.x < game->resolut_width)
		{
			game->render_data.buffer_pix[j * game->render_data.size_line / 4
				+ game->ray.x] = game->surfaces[game->material_data.dir]
				.buffer_pix[game->material_data.coord_y
				* game->surfaces[game->material_data.dir].size_line / 4
				+ game->material_data.coord_x];
		}
	}
}

static void	calculate_texture_mapping(t_game *game)
{
	game->material_data.wall_hit_x -= floor(game->material_data.wall_hit_x);
	game->material_data.step = 1.0 * game->surfaces[0].win_height
		/ game->ray.wall_height_px;
	game->material_data.coord_x = (int)(game->material_data.wall_hit_x
			* (double)game->surfaces[game->material_data.dir].win_width);
	if (game->ray.collision_side == 0 && game->ray.beam_dir_x > 0)
		game->material_data.coord_x
			= game->surfaces[game->material_data.dir].win_width
			- game->material_data.coord_x - 1;
	if (game->ray.collision_side == 1 && game->ray.beam_dir_y < 0)
		game->material_data.coord_x
			= game->surfaces[game->material_data.dir].win_width
			- game->material_data.coord_x - 1;
	game->material_data.position = (game->ray.begin_draw_px
			- game->resolut_height / 2 + game->ray.wall_height_px / 2)
		* game->material_data.step;
}

int	convert_argb_to_rgb(int color)
{
	return ((color >> 8) & 0xFFFFFF);
}

int	textur_color(t_game *game)
{
	int	j;
	int	ceiling_color_argb;
	int	floor_color_argb;

	game->ray.finish_draw_px = game->resolut_height - game->ray.begin_draw_px;
	floor_color_argb = convert_argb_to_rgb(game->floor_color);
	ceiling_color_argb = convert_argb_to_rgb(game->ceiling_color);
	set_material_direction_and_wall_hit(game);
	calculate_texture_mapping(game);
	draw_wall_pixels(game);
	j = game->ray.finish_draw_px;
	while (++j < game->resolut_height)
	{
		game->render_data.buffer_pix[j * game->render_data.size_line / 4
			+ game->ray.x] = ceiling_color_argb;
	}
	j = -1;
	while (++j < game->ray.begin_draw_px)
	{
		game->render_data.buffer_pix[j * game->render_data.size_line / 4
			+ game->ray.x] = floor_color_argb;
	}
	return (0);
}
