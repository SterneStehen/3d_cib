/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:10:16 by cpuiu             #+#    #+#             */
/*   Updated: 2024/09/05 11:10:32 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	validate_line_prefix(char *line)
{
	return (line[0] == 'F' || line[0] == 'C');
}

bool	parse_color_components(char *line, t_game *game, t_color *color)
{
	char	**split_line;

	split_line = ft_split(line + 1, ',');
	if (!split_line || ft_array_len(split_line) != 3
		|| check_str_digits(split_line[0]) || check_str_digits(split_line[1])
		|| check_str_digits(split_line[2]))
	{
		game->error_code = 2;
		error_free(game, "Color parsing error\n");
		ft_free_split(split_line);
		return (false);
	}
	color->r = ft_atoi2(split_line[0]);
	color->g = ft_atoi2(split_line[1]);
	color->b = ft_atoi2(split_line[2]);
	ft_free_split(split_line);
	return (true);
}

void	apply_color(char prefix, t_color color, t_game *game)
{
	check_color_range(game, color.r, color.g, color.b);
	if (prefix == 'F')
	{
		if (game->texture_audit[5] == 1)
			error_free(game, "Duplicate floor color definition\n");
		game->floor_color = ft_pixel(color.r, color.g, color.b);
		game->texture_audit[5] = 1;
	}
	else if (prefix == 'C')
	{
		if (game->texture_audit[4] == 1)
			error_free(game, "Duplicate ceiling color definition\n");
		game->ceiling_color = ft_pixel(color.r, color.g, color.b);
		game->texture_audit[4] = 1;
	}
}

void	set_color(char *line, t_game *game)
{
	t_color	color;

	if (!validate_line_prefix(line))
		return ;
	if (!parse_color_components(line, game, &color))
		return ;
	apply_color(line[0], color, game);
}
