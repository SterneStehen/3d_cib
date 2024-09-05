/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:49:30 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 23:34:01 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calculate_ray_step_and_grid_intersection(t_game *game)
{
	if (game->ray.beam_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.grid_x = (game->ray.pos_x - game->ray.map_x)
			* game->ray.dist_to_side_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.grid_x = (game->ray.map_x + 1.0 - game->ray.pos_x)
			* game->ray.dist_to_side_x;
	}
	if (game->ray.beam_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.grid_y = (game->ray.pos_y - game->ray.map_y)
			* game->ray.dist_to_side_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.grid_y = (game->ray.map_y + 1.0 - game->ray.pos_y)
			* game->ray.dist_to_side_y;
	}
}

static void	perform_dda_until_hit(t_game *game)
{
	while (game->ray.flag_hit == 0)
	{
		if (game->ray.grid_x < game->ray.grid_y)
		{
			game->ray.grid_x += game->ray.dist_to_side_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.collision_side = 0;
		}
		else
		{
			game->ray.grid_y += game->ray.dist_to_side_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.collision_side = 1;
		}
		if (game->level_map[game->ray.map_x][game->ray.map_y] == '1')
		{
			game->ray.flag_hit = 1;
		}
	}
}

void	draw_wall(t_game *game)
{
	calculate_ray_step_and_grid_intersection(game);
	perform_dda_until_hit(game);
	if (game->ray.collision_side == 0)
	{
		game->ray.perpwalldist = ((double)game->ray.map_x - game->ray.pos_x + (1
					- (double)game->ray.step_x) / 2) / game->ray.beam_dir_x;
	}
	else
	{
		game->ray.perpwalldist = ((double)game->ray.map_y - game->ray.pos_y + (1
					- (double)game->ray.step_y) / 2) / game->ray.beam_dir_y;
	}
	game->ray.wall_height_px = (int)(game->resolut_height
			/ game->ray.perpwalldist);
	game->ray.begin_draw_px = -game->ray.wall_height_px / 2
		+ game->resolut_height / 2;
	if (game->ray.begin_draw_px < 0)
		game->ray.begin_draw_px = 0;
	game->ray.finish_draw_px = game->ray.wall_height_px / 2
		+ game->resolut_height / 2;
	if (game->ray.finish_draw_px >= game->resolut_height
		|| game->ray.finish_draw_px < 0)
		game->ray.finish_draw_px = game->resolut_height - 1;
}
