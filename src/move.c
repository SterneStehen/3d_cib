/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:51:50 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/03 14:22:51 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	funk_a_d(t_game *game)
{
	double	move_speed;
	double	new_pos_x;
	double	new_pos_y;

	move_speed = game->ray.move_speed * 2;
	if (game->render_data.move_right == 1)
	{
		new_pos_x = game->ray.pos_x + game->ray.dir_y * move_speed;
		new_pos_y = game->ray.pos_y - game->ray.dirX * move_speed;
		if (game->level_map[(int)new_pos_x][(int)game->ray.pos_y] == '0')
			game->ray.pos_x += game->ray.dir_y * game->ray.move_speed;
		if (game->level_map[(int)game->ray.pos_x][(int)new_pos_y] == '0')
			game->ray.pos_y -= game->ray.dirX * game->ray.move_speed;
	}
	if (game->render_data.move_left == 1)
	{
		new_pos_x = game->ray.pos_x - game->ray.dir_y * move_speed;
		new_pos_y = game->ray.pos_y + game->ray.dirX * move_speed;
		if (game->level_map[(int)new_pos_x][(int)game->ray.pos_y] == '0')
			game->ray.pos_x -= game->ray.dir_y * game->ray.move_speed;
		if (game->level_map[(int)game->ray.pos_x][(int)new_pos_y] == '0')
			game->ray.pos_y += game->ray.dirX * game->ray.move_speed;
	}
}

void	funk_w_s(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	if (game->render_data.move_ahed)
	{
		new_pos_x = game->ray.pos_x + game->ray.dirX * game->ray.move_speed;
		new_pos_y = game->ray.pos_y + game->ray.dir_y * game->ray.move_speed;
		if (game->level_map[(int)new_pos_x][(int)game->ray.pos_y] == '0')
			game->ray.pos_x += game->ray.dirX * game->ray.move_speed;
		if (game->level_map[(int)game->ray.pos_x][(int)new_pos_y] == '0')
			game->ray.pos_y += game->ray.dir_y * game->ray.move_speed;
	}
	if (game->render_data.move_back)
	{
		new_pos_x = game->ray.pos_x - game->ray.dirX * game->ray.move_speed * 2;
		new_pos_y = game->ray.pos_y - game->ray.dir_y * game->ray.move_speed
			* 2;
		if (game->level_map[(int)new_pos_x][(int)game->ray.pos_y] == '0')
			game->ray.pos_x -= game->ray.dirX * game->ray.move_speed;
		if (game->level_map[(int)game->ray.pos_x][(int)new_pos_y] == '0')
			game->ray.pos_y -= game->ray.dir_y * game->ray.move_speed;
	}
}

void	funk_left_right(t_game *game)
{
	double	previos_x;
	double	previos_direct_x;
	double	rotation_angle;

	previos_x = game->ray.planX;
	previos_direct_x = game->ray.dirX;
	if (game->render_data.right_rotet == 1 || game->render_data.left_rot == 1)
	{
		if (game->render_data.right_rotet == 1)
			rotation_angle = -game->ray.rotation_speed;
		else
			rotation_angle = game->ray.rotation_speed;
		game->ray.dirX = game->ray.dirX * cos(rotation_angle) - game->ray.dir_y
			* sin(rotation_angle);
		game->ray.dir_y = previos_direct_x * sin(rotation_angle)
			+ game->ray.dir_y * cos(rotation_angle);
		game->ray.planX = game->ray.planX * cos(rotation_angle)
			- game->ray.planY * sin(rotation_angle);
		game->ray.planY = previos_x * sin(rotation_angle) + game->ray.planY
			* cos(rotation_angle);
	}
}

void	swap_images(t_game *game)
{
	void	*temp_image;
	int		*temp_buffer;

	temp_image = game->render_data.img;
	game->render_data.img = game->render_data.overlay_image;
	game->render_data.overlay_image = temp_image;
	temp_buffer = game->render_data.buffer_pix;
	game->render_data.buffer_pix = game->render_data.overlay_buffer;
	game->render_data.overlay_buffer = temp_buffer;
}
