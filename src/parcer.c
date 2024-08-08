/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:20 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/08 21:15:01 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int parse_color(char *line)
{
    int r, g, b;
    sscanf(line, "%*c %d,%d,%d", &r, &g, &b);
    return (r << 16 | g << 8 | b);
}

int *parse_map_line(char *line, int width)
{
    int *map_line = (int *)malloc(sizeof(int) * width);
    for (int i = 0; i < width; i++)
    {
        if (line[i] == ' ')
            map_line[i] = 0;
        else if (line[i] == '1')
            map_line[i] = 1;
        else if (line[i] == '0')
            map_line[i] = 0;
        else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            map_line[i] = 0;
        }
        else
        {
            free(map_line);
            return (NULL);
        }
    }
    return (map_line);
}

void parse_map(const char *file, t_data *data)
{
    FILE *fp = fopen(file, "r");
    if (!fp)
    {
        perror("Error opening map file");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int map_started = 0;
    int map_lines = 0;
    int **map = NULL;
    int map_width = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (line[0] == 'F')
            data->floorColor = parse_color(line);
        else if (line[0] == 'C')
            data->ceilingColor = parse_color(line);
        else if (strchr("012 NSEW", line[0]) != NULL)
        {
            if (!map_started)
            {
                map_started = 1;
                map_width = strlen(line) - 1;
                map = (int **)malloc(sizeof(int *) * (map_lines + 1));
            }
            map = (int **)realloc(map, sizeof(int *) * (map_lines + 1));
            map[map_lines] = parse_map_line(line, map_width);
            map_lines++;
        }
    }

    data->worldMap = map;
    data->mapWidth = map_width;
    data->mapHeight = map_lines;

    fclose(fp);
    if (line)
        free(line);
}
