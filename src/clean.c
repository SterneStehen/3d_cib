/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:05:09 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/03 14:05:38 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_textures(t_game *data)
{
	if (data->north_texture)
	{
		free(data->north_texture);
		data->north_texture = NULL;
	}
	if (data->south_texture)
	{
		free(data->south_texture);
		data->south_texture = NULL;
	}
	if (data->west_texture)
	{
		free(data->west_texture);
		data->west_texture = NULL;
	}
	if (data->east_texture)
	{
		free(data->east_texture);
		data->east_texture = NULL;
	}
}

void	free_map(t_game *data)
{
	int	i;

	if (data->level_map != NULL)
	{
		i = 0;
		while (i < data->mapHeight)
		{
			if (data->level_map[i])
			{
				free(data->level_map[i]);
				data->level_map[i] = NULL;
			}
			i++;
		}
		free(data->level_map);
		data->level_map = NULL;
	}
}

void	free_struct(t_game *game)
{
	free_textures(game);
	if (game->error_code != -1)
		free_map(game);
}

int	destroy(t_game *game)
{
	int	i;

	i = 0;
	if (game->render_data.img)
	{
		mlx_destroy_image(game->render_data.mlx_ptr, game->render_data.img);
		game->render_data.img = NULL;
	}
	while (i < 4)
	{
		if (game->surfaces[i].img)
		{
			mlx_destroy_image(game->render_data.mlx_ptr, game->surfaces[i].img);
			game->surfaces[i].img = NULL;
		}
		i++;
	}
	if (game->render_data.win)
	{
		mlx_destroy_window(game->render_data.mlx_ptr, game->render_data.win);
		game->render_data.win = NULL;
	}
	game->render_data.mlx_ptr = NULL;
	exit(0);
	return (0);
}

void	error_free(t_game *game, char *str)
{
	free_struct(game);
	if (game->render_data.mlx_ptr)
	{
		destroy(game);
	}
	else
	{
		printf("ERROR\n%s\n", str);
		exit(1);
	}
}
