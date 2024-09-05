/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:20 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 23:33:05 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_valid_key(const char *key)
{
	return (strncmp(key, "NO ", 3) == 0 || strncmp(key, "EA ", 3) == 0
		|| strncmp(key, "SO ", 3) == 0 || strncmp(key, "WE ", 3) == 0
		|| strncmp(key, " ", 1) == 0 || strncmp(key, "1", 1) == 0
		|| strncmp(key, "F ", 2) == 0 || strncmp(key, "C ", 2) == 0);
}

void	process_line(char *line, t_game *game)
{
	if (game->error_code == -1)
		error_free(game, "Parsing map errors\n");
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return ;
	}
	if (!is_valid_key(line))
		error_free(game, "Parsing key error\n");
	set_texture(line, game);
	set_map_dimensions(line, game);
	set_color(line, game);
	free(line);
}

void	parsing(char *input, t_game *game)
{
	int		fd;
	int		result;
	char	*line;

	result = 1;
	line = NULL;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_free(game, "wrong .cub \n");
	game->error_code = 0;
	while (result != 0)
	{
		result = get_next_line(fd, &line);
		process_line(line, game);
	}
	close(fd);
	if (game->map_width == 0 || game->map_height == 0 || game->error_code < 0)
		error_free(game, "Error map\n");
	map_copy(input, game);
}
