/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <7353718@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:53:05 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:05 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int calcul_arr(char **array)
{
    int length = 0;

    while (array[length] != NULL)
    {
        length++;
    }
	printf("arr_len = %d", length );
    return length;
}

static int	is_wall(int i, int j, t_game *game)
{
	if (game->level_map[i][j] == '0' || (game->level_map[i][j] != '1' && game->level_map[i][j] != ' '))
	{
		if (i == 0 || j == 0 || !game->level_map[i + 1] || !game->level_map[i][j + 1])
			return (1);
		if (game->level_map[i - 1] && game->level_map[i - 1][j] && game->level_map[i - 1][j] == ' ')
			return (1);
		if (game->level_map[i + 1] && game->level_map[i + 1][j] && game->level_map[i + 1][j] == ' ')
			return (1);
		if (game->level_map[i][j - 1] && game->level_map[i][j - 1] == ' ')
			return (1);
		if (game->level_map[i][j + 1] && game->level_map[i][j + 1] == ' ')
			return (1);
	}
	return (0);
}

static int	audit_full(int index, t_game *game)
{
	int		i;

	i = index + 1;
	while (game->level_map[i])
	{
		if (ft_strlen(game->level_map[i]) > 0)
			return (1);
		i++;
	}
	game->level_map[i] = NULL;
	return (0);
}

int	wall_check(t_game *game)
{
	int	i;
	int	j;

	if (calcul_arr(game->level_map) < 3)
		return (1);
	i = 0;
	while (game->level_map[i])
	{
		if (ft_strlen(game->level_map[i]) == 0)
		{
			if (audit_full(i, game) == 1)
				return (1);
			break;
		}
		j = 0;
		while (game->level_map[i][j])
		{
			if (is_wall(i, j, game) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int map_duble(char *line, t_game *data) {
    static int i = 0;
    int j;
    int line_length = strlen(line);  // Use strlen to get the length of the line

    j = 0;
    data->level_map[i] = NULL;

    // Allocate memory based on the actual length of the line + 1 for null-terminator
    if (!(data->level_map[i] = malloc(sizeof(char) * (line_length + 1))))
        return (0);

    while (line[j] != '\0') {
        if (init_start_position(line[j], data, i, j) == 1)
            data->level_map[i][j] = '0';
        else if (line_length == 0)
            continue; // Ignore empty line
        else
            data->level_map[i][j] = line[j];
        j++;
    }

    // Use line_length instead of data->mapWidth for null-terminator placement
    data->level_map[i][j] = '\0';
    i++;
    return (0);
}







int	map_copy(char *intput, t_game *game)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	fd = open(intput, O_RDONLY);
	if (!(game->level_map = malloc(sizeof(char *) * game->mapHeight)))
		return (0);

	while (ret != 0 )
	{
		ret = get_next_line(fd, &line);
		if (game->inside_map == 1 && game->counter1 < game->mapHeight)
			game->empty_line = 1;
	
		// Пример проверки перед обработкой строки
	if (strlen(line) == 0) 
	{
    	free(line);
		continue; // Игнорировать пустую строку
	}
		if ((game->inside_map = audit_map(line, game)) == 1)
		{
			game->counter1++;
			map_duble(line, game);
		}
		free(line);
		if (game->error_code == -1)
			error_free(game, "parsing map error2\n");
	}
	close(fd);
	game->level_map[game->mapHeight] = NULL;
	if(wall_check(game) == 1)
		error_free(game, "wall map is wrong");
	return (0);
}

int	audit_map(char *str, t_game *game)
{
	int	i;
	int	contains_map_char;

	i = 0;
	contains_map_char = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '1' || str[i] == '0')
			contains_map_char = 1;
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1'
			&& str[i] != 'N' && str[i] != 'E' && str[i] != 'W' && str[i] != 'S'
			&& str[i] != '\n' && str[i] != '\t')
		{
			if (game->inside_map == 1)
			{
				game->error_code = -1;
				printf("Invalid character '%c' in the map at position %d\n",
					str[i], i);
			}
			return (0);
		}
		i++;
	}
	if (contains_map_char)
		return (1);
	if (game->inside_map == 1)
	{
		game->error_code = -1;
		printf("Error: Map does not contain any valid map characters\n");
	}
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
	game->mapHeight = total_lines;
	game->mapWidth = max_line_length;
}
