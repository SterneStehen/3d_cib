/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:41:33 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/05 11:24:37 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/// @brief Prepares the game's rendering data and initializes 
/// the MiniLibX library.
/// @param game A pointer to the game structure to initialize 
/// rendering data for.
///
/// This function performs initial setup for the game's rendering, including:
/// - Initializing player position and movement.
/// - Initializing the MiniLibX library and handling initialization failure.
/// - Adjusting the game resolution to not exceed the maximum allowed
///  screen size.
/// - Loading textures required for the game.
/// - Creating an image buffer for rendering.
static void	run_mlx_helper(t_game *game)
{
	int	screen_width;
	int	screen_height;

	screen_width = WIN_WIDTH;
	screen_height = WIN_HEIGHT;
	init_pos_move(game);
	game->render_data.mlx_ptr = mlx_init();
	if (!game->render_data.mlx_ptr)
		error_free(game, "Mlx init impossible\n");
	if (game->resolut_width > screen_width)
		game->resolut_width = screen_width;
	else
		game->resolut_width = game->resolut_width;
	if (game->resolut_height > screen_height)
		game->resolut_height = screen_height;
	else
		game->resolut_height = game->resolut_height;
	texture_run(game);
	game->render_data.img = mlx_new_image(game->render_data.mlx_ptr,
			game->resolut_width, game->resolut_height);
	game->render_data.buffer_pix = (int *)
		mlx_get_data_addr(game->render_data.img,
			&game->render_data.bits_pix, &game->render_data.size_line,
			&game->render_data.byte_order);
}

/// @brief Initializes and runs the main loop of the MiniLibX application.
/// @param game A pointer to the game structure containing all game
/// and rendering data.
/// @return Always returns 0 to indicate success.
int	run_mlx(t_game *game)
{
	run_mlx_helper(game);
	if (game->save == 1)
		execute_raycasting(game);
	game->render_data.win = mlx_new_window(game->render_data.mlx_ptr,
			game->resolut_width, game->resolut_height, "Cub3D");
	game->render_data.overlay_image = mlx_new_image(game->render_data.mlx_ptr,
			game->resolut_width, game->resolut_height);
	game->render_data.overlay_buffer = (int *)
		mlx_get_data_addr(game->render_data.overlay_image,
			&game->render_data.bits_pix, &game->render_data.size_line,
			&game->render_data.byte_order);
	mlx_hook(game->render_data.win, 17, 0, close_win, game);
	mlx_hook(game->render_data.win, 2, 1L << 0, input_keyboard, game);
	mlx_loop_hook(game->render_data.mlx_ptr, execute_raycasting, game);
	mlx_hook(game->render_data.win, 3, 1L << 1, press_key, game);
	mlx_loop(game->render_data.mlx_ptr);
	return (0);
}
