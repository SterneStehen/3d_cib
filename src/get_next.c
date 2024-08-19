/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:49:54 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 15:27:57 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

int get_next_line(int fd, char **line, t_game *game)
{
    static char *buff = NULL;

    char *current;
    char *tmp;
	int result;
    int begin;


    if (game->error_code == 2 && buff)
    {
        free(buff);
        return 0;
    }


    if (fd < 0 || BUFFER_SIZE <= 0 || !line)
        return -1;

    *line = NULL;
    result = 1;


    if (buff)
    {

        begin = 0;
        while (buff[begin])
        {
            if (buff[begin] == '\n')
            {
                current = ft_substr(buff, 0, begin);
                tmp = *line;
                *line = ft_strjoin(*line, current);
                free(current);
                free(tmp);
                buff = ft_subbuff(buff, begin + 1, (ft_strlen(buff) - begin));
                return 1;
            }
            begin++;
        }


        current = NULL;
        if (*line)
            current = *line;
        *line = ft_strjoin(*line, buff);
        if (current)
            free(current);
        free(buff);
        buff = NULL;
    }


    if (!buff)
    {
        if (!(buff = malloc(sizeof(char) * BUFFER_SIZE + 1)))
            return -1;
    }


    while ((result = read(fd, buff, BUFFER_SIZE)) > 0)
    {
        buff[result] = '\0';
        begin = 0;
        while (buff[begin])
        {
            if (buff[begin] == '\n')
            {
                current = ft_substr(buff, 0, begin);
                tmp = *line;
                *line = ft_strjoin(*line, current);
                free(current);
                free(tmp);
                buff = ft_subbuff(buff, begin + 1, (ft_strlen(buff) - begin));
                return 1;
            }
            begin++;

        current = NULL;
        if (*line)
            current = *line;
        *line = ft_strjoin(*line, buff);
        if (current)
            free(current);
    	}
	}

    if (result <= 0)
    {
        free(buff);
        buff = NULL;
        if (*line == NULL)
        {
            *line = malloc(sizeof(char) * 1);
            if (*line)
                (*line)[0] = '\0';
        }
        return result == 0 ? 0 : -1;
    }

    return 1;
}

