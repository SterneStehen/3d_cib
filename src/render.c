/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 14:06:20 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b)
{
	return (r << 24 | g << 16 | b << 8);
}

void	calculate_distances_to_side(t_game *game)
{
	game->ray.mapX = (int)game->ray.pos_x;
	game->ray.mapY = (int)game->ray.pos_y;
	game->ray.move_speed = 0.1;
	game->ray.rotation_speed = 0.033 * 1.8;
	if (game->ray.beam_dir_y == 0)
		game->ray.dist_to_side_x = 0;
	else if (game->ray.beam_dir_x == 0)
		game->ray.dist_to_side_x = 1;
	else
		game->ray.dist_to_side_x = sqrt(1 + (game->ray.beam_dir_y
					* game->ray.beam_dir_y) / (game->ray.beam_dir_x
					* game->ray.beam_dir_x));
	if (game->ray.beam_dir_x == 0)
		game->ray.dist_to_side_y = 0;
	else if (game->ray.beam_dir_y == 0)
		game->ray.dist_to_side_y = 1;
	else
		game->ray.dist_to_side_y = sqrt(1 + (game->ray.beam_dir_x
					* game->ray.beam_dir_x) / (game->ray.beam_dir_y
					* game->ray.beam_dir_y));
	draw_wall(game);
	textur_color(game);
}

int	execute_raycasting(t_game *game)
{
	mlx_clear_window(game->render_data.mlx_ptr, game->render_data.win);
	mlx_put_image_to_window(game->render_data.mlx_ptr, game->render_data.win,
		game->render_data.img, 0, 0);
	game->ray.x = -1;
	while (game->ray.x++ < game->resolut_width)
	{
		game->ray.flag_hit = 0;
		game->ray.perpwalldist = 0;
		game->ray.cameraX = 2 * game->ray.x / (double)game->resolut_width - 1;
		game->ray.beam_dir_x = game->ray.dirX + game->ray.planX
			* game->ray.cameraX;
		game->ray.beam_dir_y = game->ray.dir_y + game->ray.planY
			* game->ray.cameraX;
		calculate_distances_to_side(game);
	}
	mlx_put_image_to_window(game->render_data.mlx_ptr, game->render_data.win,
		game->render_data.img, 0, 0);
	funk_w_s(game);
	funk_a_d(game);
	funk_left_right(game);
	swap_images(game);
	return (0);
}
