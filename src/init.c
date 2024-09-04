/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <7353718@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 02:59:34 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_start_position(char c, t_game *data, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->start_dir != 'x')
			data->is_multiplayer = 1;
		data->start_dir = c;
		data->pos_xp = i;
		data->pos_yp = j;
		return (1);
	}
	return (0);
}

void	data_init(t_data *data)
{
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

static void	extra_init(t_game *game)
{
	game->pos_xp = 0;
	game->pos_yp = 0;
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
	game->render_data.img = NULL;
	game->render_data.win = NULL;
}

void	game_init(t_game *game)
{
	int	i;

	if (!game)
		return ;
	memset(game, 0, sizeof(t_game));
	game->resolut_width = 9999;
	game->resolut_height = 9999;
	game->i = 0;
	game->floor_color = -1;
	game->ceiling_color = -1;
	// game->mapHeight = 0;
	// game->mapWidth = 0;
	game->level_map = NULL;
	game->start_dir = 'x';
	// game->texture_audit[0] = 0;
	// game->texture_audit[1] = 0;
	// game->texture_audit[2] = 0;
	// game->texture_audit[3] = 0;
	extra_init(game);
	i = 0;
	while (i < 4)
	{
		data_init(&game->surfaces[i]);
		i++;
	}
	data_init(&game->render_data);
}
