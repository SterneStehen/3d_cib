/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:22:28 by cpuiu             #+#    #+#             */
/*   Updated: 2024/09/03 14:24:20 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	input_keyboard(int sense, t_game *game)
{
	if (sense == 119 || sense == 13)
		game->render_data.move_ahed = 1;
	else if (sense == 115 || sense == 1)
		game->render_data.move_back = 1;
	else if (sense == 97 || sense == 0)
		game->render_data.move_left = 1;
	else if (sense == 100 || sense == 2)
		game->render_data.move_right = 1;
	else if (sense == 65361 || sense == 123)
		game->render_data.left_rot = 1;
	else if (sense == 65363 || sense == 124)
		game->render_data.right_rotet = 1;
	else if (sense == 65307 || sense == 53)
		error_free(game, "Esc\n");
	return (1);
}

int	press_key(int input, t_game *game)
{
	if (input == 119 || input == 13)
		game->render_data.move_ahed = 0;
	else if (input == 115 || input == 1)
		game->render_data.move_back = 0;
	else if (input == 97 || input == 0)
		game->render_data.move_left = 0;
	else if (input == 100 || input == 2)
		game->render_data.move_right = 0;
	else if (input == 65361 || input == 123)
		game->render_data.left_rot = 0;
	else if (input == 65363 || input == 124)
		game->render_data.right_rotet = 0;
	return (1);
}
