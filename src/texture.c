/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:15 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/29 01:36:58 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	texture_run(t_game *game) {
  // Массив с путями к текстурам для стен
  char *texture_paths[4] = {
      (char *)game->north_texture, (char *)game->south_texture,
      (char *)game->west_texture, (char *)game->east_texture};

  // Массив с названиями текстур для вывода ошибок
  char *texture_names[4] = {"Texture NO", "Texture SO", "Texture WE",
                            "Texture EA"};

  int i = 0;
  while (i < 4) {
    // Загрузка текстуры
    game->surfaces[i].img = mlx_xpm_file_to_image(
        game->render_data.mlx_ptr, texture_paths[i],
        &(game->surfaces[i].win_width), &(game->surfaces[i].win_height));

    // Проверка на ошибки загрузки текстуры
    if (!game->surfaces[i].img) 
    {
      error_free(game, texture_names[i]);
    }

    // Получение адреса пикселей текстуры
    game->surfaces[i].buffer_pix = (int *)mlx_get_data_addr(
        game->surfaces[i].img, &game->surfaces[i].bits_pix,
        &game->surfaces[i].size_line, &game->surfaces[i].byte_order);

    // Увеличение индекса
    i++;
  }
}


void set_texture(char *line, t_game *game)
{
    if (strncmp(line, "NO ", 3) == 0) 
    {
        game->north_texture = strdup(line + 3);
        if (!game->north_texture)
            error_free(game, "Memory allocation error for north texture\n");
    }
    else if (strncmp(line, "SO ", 3) == 0)
    {
        game->south_texture = strdup(line + 3);
        if (!game->south_texture)
            error_free(game, "Memory allocation error for south texture\n");
    }
    else if (strncmp(line, "EA ", 3) == 0) 
    {
        game->east_texture = strdup(line + 3);
        if (!game->east_texture)
            error_free(game, "Memory allocation error for east texture\n");
    }
    else if (strncmp(line, "WE ", 3) == 0)  
    {
        game->west_texture = strdup(line + 3);
        if (!game->west_texture)
            error_free(game, "Memory allocation error for west texture\n");
    }
}
