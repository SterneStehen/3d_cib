/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <7353718@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:53:05 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 15:17:55 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	validate_map_walls(t_game *data)
// {
// 	int	i;
// 	int	ret;

// 	ret = 1;
// 	// if (data->mapHeight == 0 || data->mapWidth == 0 || !data->level_map)
// 	// 	return (1);
// 	i = 0;
// 	while (i < data->mapHeight)
// 	{
// 		if (data->level_map[i][0] != '1' || data->level_map[i][data->mapWidth
// 			- 1] != '1')
// 			return (ret);
// 		i++;
// 	}
// 	i = 0;
// 	while (data->level_map[0][i] != '\0')
// 	{
// 		if (data->level_map[0][i] != '1')
// 			return (ret);
// 		i++;
// 	}
// 	i = 0;
// 	while (data->level_map[data->mapHeight - 1][i] != '\0')
// 	{
// 		if (data->level_map[data->mapHeight - 1][i] != '1')
// 			return (ret);
// 		i++;
// 	}
// 	return (0);
// }

int	map_duble(char *line, t_game *data)
{
	static int	i = 0;
	int			j;

	j = 0;
	data->level_map[i] = NULL;
	if (!(data->level_map[i] = malloc(sizeof(char) * data->mapWidth + 1)))
		return (0);
	while (line[j] != '\0')
	{
		if (init_start_position(line[j], data, i, j) == 1)
			data->level_map[i][j] = '0';
		else if (strlen(line) == 0)
			continue; // Игнорировать пустую строку
		// else if (line[j] == ' ')
		// 	data->level_map[i][j] = '1';
		else
			data->level_map[i][j] = line[j];
		j++;
	}
	while (j <= (data->mapWidth - 1))
	{
		data->level_map[i][j] = '1';
		j++;
	}
	data->level_map[i][j] = '\0';
	i++;
	return (0);
}


int leh_array(char *arr[], int rows) {
    int max_cols = 0;
    for (int i = 0; i < rows; i++) {
        if (arr[i] == NULL) {
            continue; // Пропускаем строки, которые равны NULL
        }
        int length = strlen(arr[i]); // Определяем длину каждой строки
        if (length > max_cols) {
            max_cols = length; // Находим максимальную длину строки
        }
    }
    return max_cols;
}

// Функция для печати двумерного массива строк
void printArray(char *arr[]) {
    if (arr == NULL) {
        printf("Error: The array is NULL.\n");
        return;
    }

    int rows = 0;

    // Вычисляем количество строк в массиве
    while (arr[rows] != NULL) {
        rows++;
    }

    if (rows == 0) {
        printf("Error: The array is empty.\n");
        return;
    }

    int cols = leh_array(arr, rows); // Определяем количество колонок
    printf("Rows: %d, Columns: %d\n", rows, cols);

    for (int i = 0; i < rows; i++) {
        if (arr[i] != NULL) {
            printf("%s\n", arr[i]); // Печатаем каждую строку массива
        } else {
            printf("Warning: Null string encountered.\n");
        }
    }
}


int	map_copy(char *intput, t_game *game)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	fd = open(intput, O_RDONLY);
	if (!(game->level_map = malloc(sizeof(char *) * game->mapHeight)))
		return (0);

	while (ret != 0 )
	{
		ret = get_next_line(fd, &line);
		if (game->inside_map == 1 && game->counter1 < game->mapHeight)
			game->empty_line = 1;
	
		// Пример проверки перед обработкой строки
	if (strlen(line) == 0) 
	{
    	free(line);
		continue; // Игнорировать пустую строку
	}
		if ((game->inside_map = audit_map(line, game)) == 1)
		{
			game->counter1++;
			map_duble(line, game);
		}
		free(line);
		if (game->error_code == -1)
			error_free(game, "parsing map error\n");
	}
	close(fd);
	//printArray(game->level_map);
	//if (validate_map_walls(game) == 1)
	//  error_free(game, "Map not surrounded by 1s\n");
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
		if (str[i] == '1' || str[i] == '0')
			contains_map_char = 1;
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != 'N' && str[i] != 'E' && str[i] != 'W' && str[i] != 'S'
			&& str[i] != '\n' && str[i] != '\t')
		{
			if (game->inside_map == 1)
			{
				game->error_code = -1;
				printf("Invalid character '%c' in the map at position %d\n",
					str[i], i);
			}
			return (0);
		}
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

void	check_map_data(t_game *game)
{
	if (game->floor_color == -1 || game->ceiling_color == -1
		|| game->north_texture == NULL || game->south_texture == NULL
		|| game->west_texture == NULL || game->east_texture == NULL)
	{
		game->error_code = -1;
	}
}

void	set_map_dimensions(char *line, t_game *game)
{
	int			current_line_length;
	int			is_map_line;
	static int	total_lines = 0;
	static int	max_line_length = 0;

	current_line_length = 0;
	is_map_line = audit_map(line, game);
	if (is_map_line == 1)
	{
		check_map_data(game);
		current_line_length = ft_strlen(line);
		if (current_line_length > max_line_length)
		{
			max_line_length = current_line_length;
		}
		total_lines++;
	}
	game->mapHeight = total_lines;
	game->mapWidth = max_line_length;
}
