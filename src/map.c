/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:53:05 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 22:37:02 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	validate_map_walls(t_game *data)
{
	int	i;
	int ret = 1;

	// Check if the map is empty
	if (data->mapHeight == 0 || data->mapWidth == 0 || !data->level_map)
		return (1); // Error: Map is empty or invalid

	// Check the first and last column of each row for walls ('1')
	i = 0;
	while (i < data->mapHeight)
	{
		if (data->level_map[i][0] != '1' || data->level_map[i][data->mapWidth - 1] != '1')
			return (ret); // Error: First or last column of a row is not a wall
		i++;
	}

	// Check the first row for walls ('1')
	i = 0;
	while (data->level_map[0][i] != '\0')
	{
		if (data->level_map[0][i] != '1')
			return (ret); // Error: First row is not completely walled
		i++;
	}

	// Check the last row for walls ('1')
	i = 0;
	while (data->level_map[data->mapHeight - 1][i] != '\0')
	{
		if (data->level_map[data->mapHeight - 1][i] != '1')
		{
			return (ret); // Error: Last row is not completely walled
		}
		i++;
	}
	// If all checks pass, the map is correctly walled
	ret = 0;
	
	printf("return = %d\n", ret);
	return (ret); // Success: The map is fully surrounded by walls
}

int	map_duble(char *line, t_game *data)
{
	static int	i = 0;
	int			j;

	j = 0;
	data->level_map[i] = NULL;
	if (!(data->level_map[i] = malloc(sizeof(char) * data->mapWidth + 1)))
		return (0);
	while (line[j] != '\0')
	{
		if (init_start_posicion(line[j], data, i, j) == 1)
			data->level_map[i][j] = '0';
		// else if (line[j] == ' ')
		// 	data->level_map[i][j] = '1';
		else
			data->level_map[i][j] = line[j];
		j++;
	}
	while (j <= (data->mapWidth - 1))
	{
		data->level_map[i][j] = '1';
		j++;
	}
	data->level_map[i][j] = '\0';
	i++;
	return (0);
}


int	map_copy(char *intput, t_game *game) {
  int fd;
  int ret;
  char *line;

  ret = 1;
  line = NULL;
  fd = open(intput, O_RDONLY);
  if (!(game->level_map = malloc(sizeof(char *) * game->mapHeight)))
    return (0);
  while (ret != 0) {
    ret = get_next_line(fd, &line, game);
    if (game->inside_map == 1  &&
        game->counter1 < game->mapHeight)
      game->empty_line = 1;
    if ((game->inside_map = audit_map(line, game)) == 1) {
      game->counter1++;
      map_duble(line, game);
    }
    free(line);
  }
  close(fd);
//   if (validate_map_walls(game) == 1)
//     error_free(game, "Map not surrounded by 1s\n");
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
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != 'N' && str[i] != 'E' && str[i] != 'W'
			&& str[i] != '\n' && str[i] != '\t')
		{
			if (game->inside_map == 1)
			{
				game->invalid_chars = 2;
				printf("Invalid character in the map\n");
			}
			return (0);
		}
		i++;
	}
	if (contains_map_char)
		return (1);
	return (0);
}

void	check_map_data(t_game *game)
{
	if (game->floor_color == -1 || game->ceiling_color == -1
		|| game->north_texture == NULL || game->south_texture == NULL
		|| game->west_texture == NULL || game->east_texture == NULL)
	{
		game->error_code = 2;
	}
}



void	set_map_dimensions(char *line, t_game *game)
{
	int			current_line_length;
	int 		is_map_line;
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

