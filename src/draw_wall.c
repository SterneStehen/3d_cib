/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:49:30 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 22:05:16 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void	draw_wall(t_game *game)
{
	// Инициализация шагов и начальных расстояний до ближайших сторон сетки
	if (game->ray.beam_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.grid_x = (game->ray.posX - game->ray.mapX)
			* game->ray.dist_to_side_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.grid_x = (game->ray.mapX + 1.0 - game->ray.posX)
			* game->ray.dist_to_side_x;
	}
	if (game->ray.beam_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.grid_y = (game->ray.posY - game->ray.mapY)
			* game->ray.dist_to_side_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.grid_y = (game->ray.mapY + 1.0 - game->ray.posY)
			* game->ray.dist_to_side_y;
	}
	// Инкрементальный цикл для проверки столкновений и вычисления расстояний
	while (game->ray.flag_hit == 0)
	{
		if (game->ray.grid_x < game->ray.grid_y)
		{
			game->ray.grid_x += game->ray.dist_to_side_x;
			game->ray.mapX += game->ray.step_x;
			game->ray.collision_side = 0;
		}
		else
		{
			game->ray.grid_y += game->ray.dist_to_side_y;
			game->ray.mapY += game->ray.step_y;
			game->ray.collision_side = 1;
		}
		// Проверка на столкновение с стеной ('1' в карте уровня)
		if (game->level_map[game->ray.mapX][game->ray.mapY] == '1')
		{
			game->ray.flag_hit = 1;
		}
	}
	// Расчет начальной и конечной позиции для рисования стены
	if (game->ray.collision_side == 0)
	{
		game->ray.perpwalldist = ((double)game->ray.mapX - game->ray.posX + (1
					- (double)game->ray.step_x) / 2) / game->ray.beam_dir_x;
	}
	else
	{
		game->ray.perpwalldist = ((double)game->ray.mapY - game->ray.posY + (1
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
