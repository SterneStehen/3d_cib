/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:51:50 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 22:26:53 by smoreron         ###   ########.fr       */
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

