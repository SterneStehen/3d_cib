/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:17:39 by cpuiu             #+#    #+#             */
/*   Updated: 2024/09/04 23:25:28 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_valid_map_char(char c, t_game *game)
{
	if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'E' && c != 'W'
		&& c != 'S' && c != '\n' && c != '\t')
	{
		if (game->inside_map == 1)
		{
			game->error_code = -1;
			printf("Invalid character\n");
		}
		return (0);
	}
	return (1);
}

int	contains_map_chars(char c)
{
	if (c == '1' || c == '0')
		return (1);
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
		if (contains_map_chars(str[i]))
			contains_map_char = 1;
		if (!is_valid_map_char(str[i], game))
			return (0);
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
