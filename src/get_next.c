/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:49:54 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/03 13:28:43 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	process_buffer(char **buff, char **line)
{
	char	*current;
	char	*tmp;
	int		begin;

	begin = 0;
	while ((*buff)[begin])
	{
		if ((*buff)[begin] == '\n')
		{
			current = ft_substr(*buff, 0, begin);
			tmp = *line;
			*line = ft_strjoin(*line, current);
			*buff = ft_subbuff(*buff, begin + 1, (ft_strlen(*buff) - begin));
			return (free(current), free(tmp), 1);
		}
		begin++;
	}
	current = NULL;
	if (*line)
		current = *line;
	*line = ft_strjoin(*line, *buff);
	if (current)
		free(current);
	return (free(*buff), *buff = NULL, 0);
}

static int	process_newline_in_buffer(char **buff, char **line, int *begin)
{
	char	*current;
	char	*tmp;

	while ((*buff)[*begin])
	{
		if ((*buff)[*begin] == '\n')
		{
			current = ft_substr(*buff, 0, *begin);
			tmp = *line;
			*line = ft_strjoin(*line, current);
			free(current);
			free(tmp);
			*buff = ft_subbuff(*buff, *begin + 1, (ft_strlen(*buff) - *begin));
			return (1);
		}
		(*begin)++;
	}
	return (0);
}

int	read_and_process_buffer(int fd, char **buff, char **line)
{
	int		result;
	int		begin;
	char	*current;

	result = read(fd, *buff, BUFFER_SIZE);
	while (result > 0)
	{
		(*buff)[result] = '\0';
		begin = 0;
		if (process_newline_in_buffer(buff, line, &begin))
			return (1);
		current = NULL;
		if (*line)
			current = *line;
		*line = ft_strjoin(*line, *buff);
		if (current)
			free(current);
		result = read(fd, *buff, BUFFER_SIZE);
	}
	return (result);
}

static int	finalize_and_cleanup(char **buff, char **line, int result)
{
	free(*buff);
	*buff = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		if (*line)
			(*line)[0] = '\0';
	}
	if (result == 0)
		return (0);
	else
		return (-1);
}

int	get_next_line(int fd, char **line)
{
	static char	*buff = NULL;
	int			result;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	result = 1;
	if (buff)
	{
		if (process_buffer(&buff, line))
			return (1);
	}
	if (!buff)
	{
		buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buff)
			return (-1);
	}
	result = read_and_process_buffer(fd, &buff, line);
	if (result <= 0)
		return (finalize_and_cleanup(&buff, line, result));
	return (1);
}
