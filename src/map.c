/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:53:05 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 23:05:29 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	calcul_arr(char **array)
{
	int	length;

	length = 0;
	while (array[length] != NULL)
		length++;
	return (length);
}

static int	is_wall(int i, int j, t_game *game)
{
	if (game->level_map[i][j] == '0' || (game->level_map[i][j] != '1'
			&& game->level_map[i][j] != ' '))
	{
		if (i == 0 || j == 0 || !game->level_map[i + 1] || !game->level_map[i][j
			+ 1])
			return (1);
		if (game->level_map[i - 1] && game->level_map[i - 1][j]
			&& game->level_map[i - 1][j] == ' ')
			return (1);
		if (game->level_map[i + 1] && game->level_map[i + 1][j]
			&& game->level_map[i + 1][j] == ' ')
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
	int	i;

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
	i = -1;
	while (game->level_map[++i])
	{
		if (ft_strlen(game->level_map[i]) == 0)
		{
			if (audit_full(i, game) == 1)
				return (1);
			break ;
		}
		j = 0;
		while (game->level_map[i][j])
		{
			if (is_wall(i, j, game) == 1)
				return (1);
			j++;
		}
	}
	if (game->start_dir == 'x')
		return (1);
	return (0);
}

int	map_duble(char *line, t_game *data)
{
	static int	i = 0;
	int			j;
	int			line_length;

	line_length = strlen(line);
	j = 0;
	data->level_map[i] = NULL;
	data->level_map[i] = malloc(sizeof(char) * (line_length + 1));
	if (!data->level_map[i])
		return (0);
	while (line[j] != '\0')
	{
		if (init_start_position(line[j], data, i, j) == 1)
			data->level_map[i][j] = '0';
		else if (line_length == 0)
			continue ;
		else
			data->level_map[i][j] = line[j];
		j++;
	}
	data->level_map[i][j] = '\0';
	i++;
	return (0);
}
