/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <7353718@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:36:03 by cpuiu             #+#    #+#             */
/*   Updated: 2024/09/05 02:57:58 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
		return (0);
}

long	ft_atoi2(const char *nptr)
{
	int		i;
	int		neg;
	long	num;

	i = 0;
	num = 0;
	neg = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			neg = -1 * neg;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num * neg);
}

int	check_str_digits(char *str)
{
	int	i;

	i = 0;
	printf("str = %s\n", str);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		else if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	set_color(char *line, t_game *game)
{
	char	**split_line;
	int		r;
	int		g;
	int		b;

	if (line[0] != 'F' && line[0] != 'C')
		return ;
	split_line = ft_split(line + 1, ',');
	if (!split_line || ft_array_len(split_line) != 3
		|| check_str_digits(split_line[0]) || check_str_digits(split_line[1])
		|| check_str_digits(split_line[2]))
	{
		game->error_code = 2;
		error_free(game, "Color parsing error\n");
	}
	r = ft_atoi2(split_line[0]);
	g = ft_atoi2(split_line[1]);
	b = ft_atoi2(split_line[2]);
	check_color_range(game, r, g, b);
	if (line[0] == 'F')
	{
		if (game->texture_audit[5] == 1)
			error_free(game, "Color parsing error\n");
		game->floor_color = ft_pixel(r, g, b);
		game->texture_audit[5] = 1;
	}
	else if (line[0] == 'C')
	{
		if (game->texture_audit[4] == 1)
			error_free(game, "Color parsing error\n");
		game->ceiling_color = ft_pixel(r, g, b);
		game->texture_audit[4] = 1;
	}
	ft_free_split(split_line);
}
