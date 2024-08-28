/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:05:09 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 22:23:28 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/cub3d.h"


void	free_textures(t_game *data) {
  if (data->north_texture)
    free(data->north_texture);
  if (data->south_texture)
    free(data->south_texture);
  if (data->west_texture)
    free(data->west_texture);
  if (data->east_texture)
    free(data->east_texture);
  if (data->sprite_texture)
    free(data->sprite_texture);
}

void	free_map(t_game *data) {
  int i;

  if (data->level_map) {
    i = 0;
    while (i < data->mapHeight) {
      if (data->level_map[i])
        free(data->level_map[i]);
      i++;
    }
    free(data->level_map);
  }
}

void	free_sprite_data(t_game *data) {
  if (data->sprite_data.renderOrder)
    free(data->sprite_data.renderOrder);
  if (data->sprite_data.distance)
    free(data->sprite_data.distance);
  if (data->sprites_pos)
    free(data->sprites_pos);
  if (data->sprite_data.depthBuffer)
    free(data->sprite_data.depthBuffer);
}

void	free_struct(t_game *data) {
  free_textures(data);
  free_map(data);
  free_sprite_data(data);
}

int	destroy(t_game *recup) {
  if (recup->render_data.img)
    mlx_destroy_image(recup->render_data.mlx_ptr, recup->render_data.img);
  if (recup->surfaces[0].img)
    mlx_destroy_image(recup->render_data.mlx_ptr, recup->surfaces[0].img);
  if (recup->surfaces[1].img)
    mlx_destroy_image(recup->render_data.mlx_ptr, recup->surfaces[1].img);
  if (recup->surfaces[2].img)
    mlx_destroy_image(recup->render_data.mlx_ptr, recup->surfaces[2].img);
  if (recup->surfaces[3].img)
    mlx_destroy_image(recup->render_data.mlx_ptr, recup->surfaces[3].img);
  if (recup->surfaces[4].img)
    mlx_destroy_image(recup->render_data.mlx_ptr, recup->surfaces[4].img);
  if (recup->render_data.win)
    mlx_destroy_window(recup->render_data.mlx_ptr, recup->render_data.win);
  exit(0);
}

void	error_free(t_game *data, char *str) {

  write(1, "Error\n", 6);
  write(1, str, ft_strlen(str));

  free_struct(data);

  destroy(data);
}


