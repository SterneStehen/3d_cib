/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <7353718@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:15 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 03:00:38 by smoreron         ###   ########.fr       */
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
		game->surfaces[i].buffer_pix
			= (int *)mlx_get_data_addr(game->surfaces[i].img,
				&game->surfaces[i].bits_pix, &game->surfaces[i].size_line,
				&game->surfaces[i].byte_order);
	}
}

void	set_texture(char *line, t_game *game)
{
	int fd;
	if (strncmp(line, "NO ", 3) == 0)
	{
		if(game->texture_audit[0] == 1)
			error_free(game, "duble Norton texture file fail");
			
		game->north_texture = strdup(line + 3);
		if (!game->north_texture)
			error_free(game, "Memory allocation error for north texture\n");
		
		fd = open(game->north_texture, O_RDONLY);
		if(fd == -1)
			error_free(game, "Norton texture file fail");
		//close(fd);
		game->texture_audit[0] = 1;
	}
	else if (strncmp(line, "SO ", 3) == 0)
	{
		if(game->texture_audit[1] == 1)
		 	error_free(game, "duble south_texture file fail");
		game->south_texture = strdup(line + 3);
		if (!game->south_texture)
			error_free(game, "Memory allocation error for south texture\n");
		fd = open(game->south_texture, O_RDONLY);
		if(fd == -1)
			error_free(game, "south_texture file fail");
		game->texture_audit[1] = 1;
		//close(fd);
	}
	else if (strncmp(line, "EA ", 3) == 0)
	{
		 if(game->texture_audit[2] == 1)
		 	error_free(game, "duble east_texture");
		game->east_texture = strdup(line + 3);
		if (!game->east_texture)
			error_free(game, "Memory allocation error for east texture\n");
		fd = open(game->east_texture, O_RDONLY);
		if(fd == -1)
			error_free(game, "east_texture file fail");
		game->texture_audit[2] = 1;
		//close(fd);
	}
	else if (strncmp(line, "WE ", 3) == 0)
	{
		if(game->texture_audit[3] == 1)
		 	error_free(game, "duble west_texture");
		game->west_texture = strdup(line + 3);
		if (!game->west_texture)
			error_free(game, "Memory allocation error for west texture\n");
		fd = open(game->west_texture, O_RDONLY);
		if(fd == -1)
			error_free(game, "west_texture file fail");
		game->texture_audit[3] = 1;
		//close(fd);
	}
}
