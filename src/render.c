/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/05 11:25:45 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_win(t_game *game)
{
	error_free(game, "Exit esc\n");
	exit(0);
	return (0);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b)
{
	return (r << 24 | g << 16 | b << 8);
}

/// @brief Calculates distances to the nearest side walls in the x 
// and y directions.
/// @param game A pointer to the game structure containing 
/// raycasting and rendering data.
/// This function performs the following operations:
///
///	- Initializes the ray's position on the map based on the
///  player's current position.
/// - Sets the movement and rotation speeds for the ray.
///
///	- Calculates the distance to the nearest side wall in the
/// x-direction (dist_to_side_x).
///
///	- Calculates the distance to the nearest side wall in the
/// y-direction (dist_to_side_y).
///
///	- These distances are used to perform wall collision detection 
/// and to calculate the 
/// length of the ray until it hits a wall.
/// - Finally,
///	it calls functions to draw the wall and apply texture/color based on the 
/// calculated distances.
void	calculate_distances_to_side(t_game *game)
{
	game->ray.map_x = (int)game->ray.pos_x;
	game->ray.map_y = (int)game->ray.pos_y;
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

/// @brief Executes the raycasting process for each frame and 
/// updates the game window.
/// This function is a core part of the game's rendering loop,
///	using raycasting to simulate 3D graphics in a 2D environment 
/// by casting rays from
/// the player's perspective and drawing vertical slices of 
/// walls based on the distance 
/// to obstacles.
/// @param game A pointer to the game structure containing 
/// all game and rendering data.
/// @return Always returns 0 indicating success.
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
		game->ray.camera_x = 2 * game->ray.x / (double)game->resolut_width - 1;
		game->ray.beam_dir_x = game->ray.dir_x + game->ray.plan_x
			* game->ray.camera_x;
		game->ray.beam_dir_y = game->ray.dir_y + game->ray.plan_y
			* game->ray.camera_x;
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
