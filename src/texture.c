/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:15 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 22:39:31 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	texture_run(t_game *game)
{
	int		i;
	char	*texture_paths[4];
	char	*texture_names[4];

	texture_paths[0] = game->north_texture;
	texture_paths[1] = game->south_texture;
	texture_paths[2] = game->west_texture;
	texture_paths[3] = game->east_texture;
	texture_names[0] = "North texture";
	texture_names[1] = "South texture";
	texture_names[2] = "West texture";
	texture_names[3] = "East texture";
	i = -1;
	while (++i < 4)
	{
		game->surfaces[i].img = mlx_xpm_file_to_image(game->render_data.mlx_ptr,
				texture_paths[i], &(game->surfaces[i].win_width),
				&(game->surfaces[i].win_height));
		if (!game->surfaces[i].img)
			error_free(game, texture_names[i]);
		game->surfaces[i].buffer_pix = (int *)
			mlx_get_data_addr(game->surfaces[i].img,
				&game->surfaces[i].bits_pix, &game->surfaces[i].size_line,
				&game->surfaces[i].byte_order);
	}
}

void	load_texture(char *line, char **texture, int *audit, t_game *game)
{
	int	fd;

	if (*audit == 1)
		error_free(game, "error textures duplicated\n");
	*texture = strdup(line + 3);
	if (!*texture)
		error_free(game, "Memory allocation error for texture\n");
	fd = open(*texture, O_RDONLY);
	if (fd == -1)
		error_free(game, "Texture file loading failed\n");
	*audit = 1;
	close(fd);
}

void	set_texture(char *line, t_game *game)
{
	if (strncmp(line, "NO ", 3) == 0)
		load_texture(line, &game->north_texture, &game->texture_audit[0], game);
	else if (strncmp(line, "SO ", 3) == 0)
		load_texture(line, &game->south_texture, &game->texture_audit[1], game);
	else if (strncmp(line, "EA ", 3) == 0)
		load_texture(line, &game->east_texture, &game->texture_audit[2], game);
	else if (strncmp(line, "WE ", 3) == 0)
		load_texture(line, &game->west_texture, &game->texture_audit[3], game);
}
