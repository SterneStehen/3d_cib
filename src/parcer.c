/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:20 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 23:24:20 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	print_map(t_game *game) {
  int i;
  int j;

  printf("Starting to print the map...\n");
  if (!game || !game->level_map) {
    printf("No map to display.\n");
    return ;
  }
  printf("Map dimensions: height = %d, width = %d\n", game->mapHeight,
         game->mapWidth);
  for (i = 0; i < game->mapHeight; i++) {
    if (!game->level_map[i]) // Проверка
    {
      printf("Row %d is not initialized.\n", i);
      continue ;
    }
    for (j = 0; j < game->mapWidth; j++) {
      printf("%c", game->level_map[i][j]);
    }
    printf("\n");
  }
  printf("Finished printing the map.\n");
}

void	print_game_info(t_game *game) {
  if (!game) {
    printf("No game data to display.\n");
    return ;
  }
 
  //printf("Resolution: %d x %d\n", game->resolut_width, game->resolut_height);
 
  printf("Floor color: %d\n", game->floor_color);
  printf("Ceiling color: %d\n", game->ceiling_color);
  
  printf("North texture: %s\n",
         game->north_texture ? game->north_texture : "Not set");
  printf("South texture: %s\n",
         game->south_texture ? game->south_texture : "Not set");
  printf("East texture: %s\n",
         game->east_texture ? game->east_texture : "Not set");
  printf("West texture: %s\n",
         game->west_texture ? game->west_texture : "Not set");
  printf("Sprite texture: %s\n",
         game->sprite_texture ? game->sprite_texture : "Not set");
  // print card
  print_map(game);
  //print_sprite_positions(game);
}


int *parse_map_line(char *line, int width)
{
    int *map_line = (int *)malloc(sizeof(int) * width);
    for (int i = 0; i < width; i++)
    {
        if (line[i] == ' ')
            map_line[i] = 0;
        else if (line[i] == '1')
            map_line[i] = 1;
        else if (line[i] == '0')
            map_line[i] = 0;
        else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            map_line[i] = 0;
        }
        else
        {
            free(map_line);
            return (NULL);
        }
    }
    return (map_line);
}

void	parsing(char *input, t_game *game) {
  int fd;
  int ret;
  char *line;

  ret = 1;
  line = NULL;
  if ((fd = open(input, O_RDONLY)) == -1)
    error_free(game, "wrong .cub \n");
  game->error_code = 0;
  while (ret != 0) {
    ret = get_next_line(fd, &line, game);
    if (game->error_code == 2)
      error_free(game, "parsing map error\n");
    //set_resolution(line, game);
    set_texture(line, game);
    set_map_dimensions(line, game);
    set_color(line, game);
    free(line);
  }
  close(fd);
  if (game->mapWidth == 0 || game->mapHeight == 0 || game->error_code == 2)
    error_free(game, "Error map\n");
  map_copy(input, game);
  print_game_info(game);
}
