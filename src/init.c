/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 14:26:38 by smoreron         ###   ########.fr       */
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

void	ft_init_game(t_game *game) {

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
  while (i < 5) {
    ft_init_data(&game->surfaces[i]);
    i++;
  }
  ft_init_data(&game->render_data);
}
