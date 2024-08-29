/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:41:33 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/29 01:37:25 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int run_mlx(t_game *game) 
{
  // Initialize the starting position and movement settings
  init_pos_move(game);

  // Initialize the miniLibX library
  game->render_data.mlx_ptr = mlx_init();
  if (!game->render_data.mlx_ptr) {
    // If initialization fails, handle the error and free resources
    error_free(game, "Mlx init impossible\n");
  }

  // Determine the screen size and adjust the resolution accordingly
  int screen_width, screen_height;
  mlx_get_screen_size(game->render_data.mlx_ptr, &screen_width, &screen_height);
  game->resolut_width =
      (game->resolut_width > screen_width) ? screen_width : game->resolut_width;
  game->resolut_height = (game->resolut_height > screen_height)
                             ? screen_height
                             : game->resolut_height;

  // Initialize textures
  texture_run(game);

  // Create a new image for rendering
  game->render_data.img = mlx_new_image(
      game->render_data.mlx_ptr, game->resolut_width, game->resolut_height);
  game->render_data.buffer_pix = (int *)mlx_get_data_addr(
      game->render_data.img, &game->render_data.bits_pix,
      &game->render_data.size_line, &game->render_data.byte_order);

  // Perform raycasting if the save flag is set
  if (game->save == 1) {
    execute_raycasting(game);
  }

  // Create a window for displaying the game
  game->render_data.win =
      mlx_new_window(game->render_data.mlx_ptr, game->resolut_width,
                     game->resolut_height, "Cub3D");

  // Create an additional image for overlay rendering
  game->render_data.overlay_image = mlx_new_image(
      game->render_data.mlx_ptr, game->resolut_width, game->resolut_height);
  game->render_data.overlay_buffer = (int *)mlx_get_data_addr(
      game->render_data.overlay_image, &game->render_data.bits_pix,
      &game->render_data.size_line, &game->render_data.byte_order);

  // Set up event handlers
  mlx_hook(game->render_data.win, 33, 1L << 17, destroy,
           game); // Handle window close event
  mlx_hook(game->render_data.win, 2, 1L << 0, input_keyboard,
           game); // Handle key press events
  mlx_loop_hook(game->render_data.mlx_ptr, execute_raycasting,
                game); // Main loop for executing raycasting
  mlx_hook(game->render_data.win, 3, 1L << 1, press_key,
           game); // Handle key release events

  // Start the main miniLibX loop
  mlx_loop(game->render_data.mlx_ptr);

  return (0);
}
