/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:53:05 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 15:30:20 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



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
		else if (line[j] == ' ')
			data->level_map[i][j] = '1';
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


int	map_copy(char *input, t_game *game) {
  int fd;
  int ret;
  char *line;

  ret = 1;
  line = NULL;
  fd = open(input, O_RDONLY);
  if (!(game->level_map = malloc(sizeof(char *) * game->mapHeight)))
    return (0);
  while (ret != 0) {
    ret = get_next_line(fd, &line, game);
    if (game->inside_map == 1 && is_line_empty(line) == 0 &&
        game->counter1 < game->mapHeight)
      game->empty_line = 1;
    if ((game->inside_map = audit_map(line, game)) == 1) {
      game->counter1++;
      map_duble(line, game);
    }
    free(line);
  }
  close(fd);
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
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W'
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
		|| game->west_texture == NULL || game->east_texture == NULL
		|| game->sprite_texture == NULL)
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

