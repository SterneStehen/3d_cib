/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:51:50 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/29 07:15:17 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

int	input_keyboard(int sense, t_game *game)
{
	if (sense == 119 || sense == 13) // W: 119 (Linux), 13 (macOS)
		game->render_data.move_ahed = 1;
	else if (sense == 115) // S: 115 (Linux), 1 (macOS)
		game->render_data.move_back = 1;
	else if (sense == 97 || sense == 0) // A: 97 (Linux), 0 (macOS)
		game->render_data.move_left = 1;
	else if (sense == 100 || sense == 2) // D: 100 (Linux), 2 (macOS)
		game->render_data.move_right = 1;
	else if (sense == 65361 || sense == 123) // LEFT: 65361 (Linux), 123 (macOS)
		game->render_data.left_rot = 1;
	else if (sense == 65363 || sense == 124) // RIGHT: 65363 (Linux)
		game->render_data.right_rotet = 1;
	else if (sense == 65307 || sense == 53) // Escape: 65307 (Linux), 53 (macOS)
		error_free(game, "Esc\n");
	return (1);
}

int	press_key(int input, t_game *game)
{
	if (input == 119 || input == 13) // W: 119 (Linux), 13 (macOS)
		game->render_data.move_ahed = 0;
	else if (input == 115) // S: 115 (Linux), 1 (macOS)
		game->render_data.move_back = 0;
	else if (input == 97 || input == 0) // A: 97 (Linux), 0 (macOS)
		game->render_data.move_left = 0;
	else if (input == 100 || input == 2) // D: 100 (Linux), 2 (macOS)
		game->render_data.move_right = 0;
	else if (input == 65361 || input == 123) // LEFT: 65361 (Linux), 123 (macOS)
		game->render_data.left_rot = 0;
	else if (input == 65363 || input == 124) // RIGHT: 65363 (Linux),124 (macOS)
		game->render_data.right_rotet = 0;
	return (1);
}


void funk_A_D(t_game *game) {
    double moveSpeed = game->ray.move_speed * 2;
    double newPosX, newPosY;

    if (game->render_data.move_right == 1) {
        // Рассчитываем новые координаты при движении вправо
        newPosX = game->ray.posX + game->ray.dirY * moveSpeed;
        newPosY = game->ray.posY - game->ray.dirX * moveSpeed;

        // Проверяем возможность перемещения на новые координаты
        if (game->level_map[(int)newPosX][(int)game->ray.posY] == '0')
            game->ray.posX += game->ray.dirY * game->ray.move_speed;
        if (game->level_map[(int)game->ray.posX][(int)newPosY] == '0')
            game->ray.posY -= game->ray.dirX * game->ray.move_speed;
    }

    if (game->render_data.move_left == 1) {
        // Рассчитываем новые координаты при движении влево
        newPosX = game->ray.posX - game->ray.dirY * moveSpeed;
        newPosY = game->ray.posY + game->ray.dirX * moveSpeed;

        // Проверяем возможность перемещения на новые координаты
        if (game->level_map[(int)newPosX][(int)game->ray.posY] == '0')
            game->ray.posX -= game->ray.dirY * game->ray.move_speed;
        if (game->level_map[(int)game->ray.posX][(int)newPosY] == '0')
            game->ray.posY += game->ray.dirX * game->ray.move_speed;
    }
}

void	funk_W_S(t_game *game)
{
	// Move forward
	if (game->render_data.move_ahed)
	{
		// Calculate potential new positions based on the current direction and speed
		double newPosX = game->ray.posX + game->ray.dirX * game->ray.move_speed * 2;
		double newPosY = game->ray.posY + game->ray.dirY * game->ray.move_speed * 2;

		// Check if the next position on the X-axis is within the map and not a wall
		if (game->level_map[(int)newPosX][(int)game->ray.posY] == '0')
			game->ray.posX += game->ray.dirX * game->ray.move_speed;

		// Check if the next position on the Y-axis is within the map and not a wall
		if (game->level_map[(int)game->ray.posX][(int)newPosY] == '0')
			game->ray.posY += game->ray.dirY * game->ray.move_speed;
	}

	// Move backward
	if (game->render_data.move_back)
	{
		// Calculate potential new positions based on the current direction and speed
		double newPosX = game->ray.posX - game->ray.dirX * game->ray.move_speed * 2;
		double newPosY = game->ray.posY - game->ray.dirY * game->ray.move_speed * 2;

		// Check if the next position on the X-axis is within the map and not a wall
		if (game->level_map[(int)newPosX][(int)game->ray.posY] == '0')
			game->ray.posX -= game->ray.dirX * game->ray.move_speed;

		// Check if the next position on the Y-axis is within the map and not a wall
		if (game->level_map[(int)game->ray.posX][(int)newPosY] == '0')
			game->ray.posY -= game->ray.dirY * game->ray.move_speed;
	}
}


void	funk_left_right(t_game *game)
{
	double	previos_X;
	double	previos_direct_X;
	double	rotation_angle;

	previos_X = game->ray.planX;
	previos_direct_X = game->ray.dirX;

	// Check if either left or right rotation is triggered
	if (game->render_data.right_rotet == 1 || game->render_data.left_rot == 1)
	{
		// Set the rotation angle based on direction
		if (game->render_data.right_rotet == 1)
			rotation_angle = -game->ray.rotation_speed / 2; // Rotate right
		else
			rotation_angle = game->ray.rotation_speed / 2;  // Rotate left

		// Calculate new direction vector
		game->ray.dirX = game->ray.dirX * cos(rotation_angle)
			- game->ray.dirY * sin(rotation_angle);
		game->ray.dirY = previos_direct_X * sin(rotation_angle)
			+ game->ray.dirY * cos(rotation_angle);

		// Calculate new plane vector for camera
		game->ray.planX = game->ray.planX * cos(rotation_angle)
			- game->ray.planY * sin(rotation_angle);
		game->ray.planY = previos_X * sin(rotation_angle)
			+ game->ray.planY * cos(rotation_angle);
	}
}

void	swap_images(t_game *game)
{
	// Temporary variables to hold current image and buffer data
	void	*temp_image;
	int		*temp_buffer;

	// Swapping the main rendering image with the overlay image
	temp_image = game->render_data.img;
	game->render_data.img = game->render_data.overlay_image;
	game->render_data.overlay_image = temp_image;

	// Swapping the main buffer with the overlay buffer
	temp_buffer = game->render_data.buffer_pix;
	game->render_data.buffer_pix = game->render_data.overlay_buffer;
	game->render_data.overlay_buffer = temp_buffer;

	// Logging to track image swapping
	printf("Swapped main image with overlay image.\n");
	printf("Swapped main buffer with overlay buffer.\n");
}
