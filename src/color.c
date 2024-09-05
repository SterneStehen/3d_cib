/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/05 00:36:53 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	find_end(const char *s, char c, int i)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static void	ft_clean(char ***arr, int index)
{
	while (index > 0)
		free((*arr)[--index]);
	free(*arr);
	*arr = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		arr[4];
	char	**result;

	arr[0] = 0;
	arr[3] = 0;
	result = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!result || !s)
		return (NULL);
	while (s[arr[0]])
	{
		arr[1] = find_start(s, c, arr[0]);
		arr[2] = find_end(s, c, arr[1]);
		if (arr[2] > arr[1])
		{
			result[arr[3]] = ft_substr(s, arr[1], arr[2] - arr[1]);
			if (result[arr[3]] == NULL)
				return (ft_clean(&result, arr[3]), NULL);
			arr[3]++;
		}
		arr[0] = arr[2];
	}
	result[arr[3]] = NULL;
	return (result);
}

void	check_color_range(t_game *game, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		game->error_code = 2;
		error_free(game, "Color value out of range\n");
	}
}
