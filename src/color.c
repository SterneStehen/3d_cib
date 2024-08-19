/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 13:39:21 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "../include/cub3d.h"

void	ft_free_split(char **split)
{
	int i;

	if (!split)
		return;
	
	i = 0;
	while (split[i])
	{
		free(split[i]); 
		i++;
	}
	free(split);
}



int	ft_array_len(char **array)
{
	int len = 0;

	while (array[len])
		len++;
	return (len);
}


int	ft_word_count(char const *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == c)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static int	find_start(const char *s, char c, int i)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

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




void	set_color(char *line, t_game *game)
{
	char	**split_line;
	int		r, g, b;

	if (line[0] != 'F' && line[0] != 'C')
		return ;

	split_line = ft_split(line + 1, ',');
	if (!split_line || ft_array_len(split_line) != 3)
	{
		game->error_code = 2;
		error_free(game, "Color parsing error\n");
	}

	r = atoi(split_line[0]);
	g = atoi(split_line[1]);
	b = atoi(split_line[2]);
	printf("r = %d, g = %d, b = %d\n", r, g, b);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		game->error_code = 2;
		error_free(game, "Color value out of range\n");
	}

	if (line[0] == 'F')
		game->floor_color = (r << 16) | (g << 8) | b; // Store RGB as a single integer
	else if (line[0] == 'C')
		game->ceiling_color = (r << 16) | (g << 8) | b;
	
	//int color = 16716830;

	// int r = (color >> 16) & 0xFF;
	// int g = (color >> 8) & 0xFF;
	// int b = color & 0xFF;

	ft_free_split(split_line);
	
}

