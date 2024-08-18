/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/18 16:54:36 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data) {
  // Set player initial position and direction
  data->player.posX = 22.0; // Example starting position X
  data->player.posY = 12.0; // Example starting position Y
  data->player.dirX = -1.0; // Facing West
  data->player.dirY = 0.0;  // No vertical component in direction
  data->player.planeX = 0.0;
  data->player.planeY = 0.66; // Camera plane perpendicular to direction
}

void	init_window(t_data *data) {
  // Initialize the window using MiniLibX
  data->mlx_ptr = mlx_init();
  if (data->mlx_ptr == NULL) {
    perror("Error initializing MLX");
    exit(1);
  }

  data->win = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
  if (data->win == NULL) {
    perror("Error creating window");
    exit(1);
  }
}

void	init_image(t_data *data) {
  // Initialize the image buffer
  data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
  if (data->img.img_ptr == NULL) {
    perror("Error creating image");
    exit(1);
  }

  data->img.data = (int *)mlx_get_data_addr(
      data->img.img_ptr, &data->img.bpp, &data->img.size_l, &data->img.endian);
  if (data->img.data == NULL) {
    perror("Error getting image data address");
    exit(1);
  }
}

void	init_map(t_data *data, const char *map_file) {
  // Parse the map file to initialize the world map and other settings
  parse_map(map_file, data);
}

void	init_game(t_data *data, const char *map_file) {
  // Call the initialization functions
  init_player(data);
  init_window(data);
  init_image(data);
  init_map(data, map_file);
}

void	ft_init_data(t_data *data) {
  if (!data)
    return ;

  data->bits_pix = 0;
  data->size_line = 0;
  data->byte_order = 0;
  data->move_ahed = 0;
  data->move_back = 0;
  data->move_left = 0;
  data->move_right = 0;
  data->left_rot = 0;
  data->right_rotet = 0;
  data->minimap_scale = 0;
  data->win_width = 0;
  data->win_height = 0;
  data->buffer_pix = NULL;
  data->overlay_buffer = NULL;
  data->overlay_image = NULL;
  data->mlx_ptr = NULL;
  data->win = NULL;
  data->img = NULL;
}

void	ft_init_game(t_game *game) {
  int i;

  if (!game)
    return ;

  game->resolut_width = 0;
  game->resolut_height = 0;
  game->i = 0;
  game->floor_color =
      -1; // Обычно используется -1 для обозначения "неопределенного" состояния.
  game->ceiling_color = -1; // Аналогично для потолка.
  game->mapHeight = 0;
  game->mapWidth = 0;
  game->level_map = NULL;
  game->start_dir = 'x'; // Неопределенное направление.
  game->posXp = 0;
  game->posYp = 0;
  game->viewport_width = 0;
  game->viewport_height = 0;
  game->is_multiplayer = 0;
  game->empty_line = 0;
  game->inside_map = 0;
  game->total_sum = 0;
  game->invalid_chars = 0;
  game->north_texture = NULL;
  game->south_texture = NULL;
  game->west_texture = NULL;
  game->east_texture = NULL;
  game->sprite_texture = NULL;
  game->sprites_pos = NULL;

  int i = 0;
  while (i < 5) {
    ft_init_data(&game->surfaces[i]);
    i++;
  }
  ft_init_data(&game->render_data);
}
