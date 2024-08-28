/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 21:46:39 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_start_posicion(char c, t_game *data, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->start_dir != 'x')
			data->is_multiplayer = 1;
		data->start_dir = c;
		data->posXp = i;
		data->posYp = j;
		return (1);
	}
	return (0);
}


void	ft_init_data(t_data *data) {
  if (!data)
    return ;

  
  data->buffer_pix = NULL;
  data->overlay_buffer = NULL;
  data->overlay_image = NULL;
  data->mlx_ptr = NULL;
  data->win = NULL;
  data->img = NULL;
}

void	game_init(t_game *game) {

  if (!game)
    return ;

  game->resolut_width = 0;
  game->resolut_height = 0;
  game->i = 0;
  game->floor_color =
      -1; 
  game->ceiling_color = -1; 
  game->mapHeight = 0;
  game->mapWidth = 0;
  game->level_map = NULL;
  game->start_dir = 'x'; 
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

  int i = 0;
  while (i < 4) {
    ft_init_data(&game->surfaces[i]);
    i++;
  }
  ft_init_data(&game->render_data);
}


void	sprite_start(t_game *game) {
    int row;
    int col;
    int sprite_count;

    // Initialize the sprite count to zero
    game->sprite_data.count = 0;

    // Scan the map to count the sprites
    for (row = 0; row < game->mapHeight; row++) {
        for (col = 0; col < game->mapWidth; col++) {
            if (game->level_map[row][col] == '2') {
                game->sprite_data.count++;
            }
        }
    }

    // Allocate memory for sprite positions and related data
    size_t sprite_count_size = game->sprite_data.count * sizeof(е_point2D);
    game->sprites_pos = (е_point2D *)malloc(sprite_count_size);
    if (!game->sprites_pos) {
        error_free(game, "Failed to allocate memory for sprite positions");
    }

    game->sprite_data.renderOrder = (int *)malloc(game->sprite_data.count * sizeof(int));
    if (!game->sprite_data.renderOrder) {
        error_free(game, "Failed to allocate memory for render order");
    }

    game->sprite_data.distance = (double *)malloc(game->sprite_data.count * sizeof(double));
    if (!game->sprite_data.distance) {
        error_free(game, "Failed to allocate memory for sprite distances");
    }

    // Populate sprite positions
    sprite_count = 0;
    for (row = 0; row < game->mapHeight; row++) {
        for (col = 0; col < game->mapWidth; col++) {
            if (game->level_map[row][col] == '2') {
                game->sprites_pos[sprite_count].x = row + 0.5;
                game->sprites_pos[sprite_count].y = col + 0.5;
                sprite_count++;
            }
        }
    }
    init_pos_move(game);
}



void	init_pos_move(t_game *game) {
    // Memory allocation for depth buffer
    if (!(game->sprite_data.depthBuffer = (double *)malloc(sizeof(double) * MAX_BUFFER_SIZE)))
        exit(0);

    // Initialization of movement parameters
    game->render_data.move_ahed = 0;
    game->render_data.move_back = 0;
    game->render_data.move_left = 0;
    game->render_data.move_right = 0;
    game->render_data.right_rotet = 0;
    game->render_data.left_rot = 0;

    // Initialization of starting position and direction
    game->ray.posX = (double)game->posXp + 0.5;
    game->ray.posY = (double)game->posYp + 0.5;
    game->ray.dirX = 0;
    game->ray.dirY = 0;
    game->ray.planX = 0;
    game->ray.planY = 0;

    // Setting initial direction and plane based on start direction
    if (game->start_dir == 'N') {
        game->ray.dirX = -1;
        game->ray.planY = 0.5;
    } else if (game->start_dir == 'S') {
        game->ray.dirX = 1;
        game->ray.planY = -0.5;
    } else if (game->start_dir == 'E') {
        game->ray.dirY = 1;
        game->ray.planX = 0.5;
    } else if (game->start_dir == 'W') {
        game->ray.dirY = -1;
        game->ray.planX = -0.5;
    }
}
