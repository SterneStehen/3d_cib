/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:35 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/18 22:58:52 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	is_char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}



int	process_resolution(char *str, t_game *game)
{
	if (str[0] == 'R')
	{
		if (game->resolut_width != 0 && game->resolut_height != 0)
		{
			game->error_code = 2;
			return (0);
		}
		str++;
		if (str[0] != ' ' || is_char_in_str(str, ',') == 1)
		{
			game->error_code = 2;
			return (0);
		}

		while (*str == ' ')
			str++;
		game->resolut_width = atoi(str);
		while (*str >= '0' && *str <= '9')
			str++;
		while (*str == ' ')
			str++;
		game->resolut_height = atoi(str);
		if (game->resolut_width <= 0 || game->resolut_height <= 0)
		{
			game->error_code = 2;
		}
		while (*str >= '0' && *str <= '9')
			str++;
		while (*str == ' ')
			str++;
		if (*str != '\0')
		{
			game->error_code = 2;
		}
	}
	return (0);
}
