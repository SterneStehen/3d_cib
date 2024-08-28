/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:05:09 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/29 00:55:10 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/cub3d.h"

#include <stdlib.h>
#include <unistd.h> // для write

void	free_textures(t_game *data) {
	if (data->north_texture) {
		free(data->north_texture);
		data->north_texture = NULL;
		printf("North texture freed.\n");
	}
	if (data->south_texture) {
		free(data->south_texture);
		data->south_texture = NULL;
		printf("South texture freed.\n");
	}
	if (data->west_texture) {
		free(data->west_texture);
		data->west_texture = NULL;
		printf("West texture freed.\n");
	}
	if (data->east_texture) {
		free(data->east_texture);
		data->east_texture = NULL;
		printf("East texture freed.\n");
	}
}

void	free_map(t_game *data) {
	int i;

	if (data->level_map != NULL ) 
  {
		i = 0;
		while (i < data->mapHeight) 
    {
			if (data->level_map[i]) 
      {
				free(data->level_map[i]);
				data->level_map[i] = NULL;
				printf("Map row %d freed.\n", i);
			}
			i++;
		}
		free(data->level_map);
		data->level_map = NULL;
		printf("Level map freed.\n");
	}
}

// void	free_sprite_data(t_game *data) {
// 	if (data->sprite_data.renderOrder) {
// 		free(data->sprite_data.renderOrder);
// 		data->sprite_data.renderOrder = NULL;
// 		printf("Sprite render order freed.\n");
// 	}
// 	if (data->sprite_data.distance) {
// 		free(data->sprite_data.distance);
// 		data->sprite_data.distance = NULL;
// 		printf("Sprite distances freed.\n");
// 	}
// 	if (data->sprites_pos) {
// 		free(data->sprites_pos);
// 		data->sprites_pos = NULL;
// 		printf("Sprite positions freed.\n");
// 	}
// 	if (data->sprite_data.depthBuffer) {
// 		free(data->sprite_data.depthBuffer);
// 		data->sprite_data.depthBuffer = NULL;
// 		printf("Sprite depth buffer freed.\n");
// 	}
// }

void	free_struct(t_game *game) {
	free_textures(game);
	if(game->error_code != -1)
    free_map(game);
	//free_sprite_data(game);
}

int	destroy(t_game *game) {
	if (game->render_data.img) {
		mlx_destroy_image(game->render_data.mlx_ptr, game->render_data.img);
		game->render_data.img = NULL;
		printf("Main image destroyed.\n");
	}
	for (int i = 0; i < 4; i++) {
		if (game->surfaces[i].img) {
			mlx_destroy_image(game->render_data.mlx_ptr, game->surfaces[i].img);
			game->surfaces[i].img = NULL;
			printf("Surface %d image destroyed.\n", i);
		}
	}
	if (game->render_data.win) {
		mlx_destroy_window(game->render_data.mlx_ptr, game->render_data.win);
		game->render_data.win = NULL;
		printf("Window destroyed.\n");
	}
	// Обнулим указатель на библиотеку, чтобы предотвратить повторное использование
	game->render_data.mlx_ptr = NULL;
	exit(0); // Завершаем программу после освобождения всех ресурсов
	return (0);
}

void	error_free(t_game *game, char *str) {
	write(1, "bay\n", 4);
	write(1, str, ft_strlen(str));

	free_struct(game);


	if (game->render_data.mlx_ptr) {
		destroy(game);
	} else {
		printf("MLX not initialized, exiting directly.\n");
		exit(1); // Завершаем программу, если ресурсы не были инициализированы
	}
}


