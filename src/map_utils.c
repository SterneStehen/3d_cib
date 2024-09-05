/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:02:59 by cpuiu             #+#    #+#             */
/*   Updated: 2024/09/04 23:32:51 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	process_map_file(int fd, t_game *game)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (game->inside_map == 1 && game->counter1 < game->map_height)
			game->empty_line = 1;
		if (strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		game->inside_map = audit_map(line, game);
		if (game->inside_map == 1)
		{
			game->counter1++;
			map_duble(line, game);
		}
		free(line);
		if (game->error_code == -1)
			error_free(game, "Parsing map error2\n");
	}
}

int	map_copy(char *input, t_game *game)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		error_free(game, "Error: Map file not found\n");
	game->level_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!(game->level_map))
		return (0);
	process_map_file(fd, game);
	close(fd);
	game->level_map[game->map_height] = NULL;
	if (wall_check(game) == 1)
		error_free(game, "Wall map is wrong");
	return (0);
}

void	check_map_data(t_game *game)
{
	if (game->floor_color == -1 || game->ceiling_color == -1
		|| game->north_texture == NULL || game->south_texture == NULL
		|| game->west_texture == NULL || game->east_texture == NULL)
	{
		game->error_code = -1;
	}
}

void	set_map_dimensions(char *line, t_game *game)
{
	int			current_line_length;
	int			is_map_line;
	static int	total_lines = 0;
	static int	max_line_length = 0;

	current_line_length = 0;
	is_map_line = audit_map(line, game);
	if (is_map_line == 1)
	{
		check_map_data(game);
		current_line_length = ft_strlen(line);
		if (current_line_length > max_line_length)
		{
			max_line_length = current_line_length;
		}
		total_lines++;
	}
	game->map_height = total_lines;
	game->map_width = max_line_length;
}
