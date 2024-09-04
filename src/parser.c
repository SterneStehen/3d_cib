/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <7353718@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:20 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 21:48:07 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


bool is_valid_key(const char *key) {
    return (strncmp(key, "NO ", 3) == 0 ||
            strncmp(key, "EA ", 3) == 0 ||
            strncmp(key, "SO ", 3) == 0 ||
            strncmp(key, "WE ", 3) == 0 ||
            strncmp(key, " ", 1) == 0 ||
			strncmp(key, "1", 1) == 0 ||
			strncmp(key, "F ", 2) == 0 ||
            strncmp(key, "C ", 2) == 0);		
}


// int	*parse_map_line(char *line, int width)
// {
// 	int	*map_line;
// 	int	i;

// 	i = 0;
// 	map_line = (int *)malloc(sizeof(int) * width);
// 	while (i < width)
// 	{
// 		if (line[i] == ' ')
// 			map_line[i] = 0;
// 		else if (line[i] == '1')
// 			map_line[i] = 1;
// 		else if (line[i] == '0')
// 			map_line[i] = 0;
// 		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
// 			|| line[i] == 'W')
// 			map_line[i] = 0;
// 		else
// 		{
// 			error_free(game, "fail map");
// 		}
// 		i++;
// 	}
// 	return (map_line);
// }


void print_map(t_game *game)
{
    int i;

    if (!game->level_map)
    {
        printf("New_Map is not loaded.\n");
        return;
    }

    i = 0;
    printf("Game map:\n");

    // Проверяем длину массива перед использованием
    int length = calcul_arr(game->level_map);
    printf("Map length: %d\n", length);

    while (i < length)
    {
        if (game->level_map[i] != NULL)
        {
            printf("%s\n", game->level_map[i]);
        }
        else
        {
            printf("NULL string found at index %d\n", i);
        }
        i++;
    }
}

void	parsing(char *input, t_game *game)
{
	int		fd;
	int		result;
	char	*line;
	

	result = 1;
	line = NULL;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_free(game, "wrong .cub \n");
	
	game->error_code = 0;
	while (result != 0)
	{
		result = get_next_line(fd, &line);
		if (game->error_code == -1)
			error_free(game, "parsing map errors\n");
		if(line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue;
		}
		if(!is_valid_key(line))
		{
			error_free(game, "parsing key error\n");
		}
		set_texture(line, game);
		set_map_dimensions(line, game);
		set_color(line, game);
		

		free(line);
	}
	close(fd);
	
	// if (game->north_texture == 0 || game->south_texture == 0 || game->west_texture == 0 || game->east_texture == 0) 
	// 	error_free(game, "Error texture\n");
	if (game->mapWidth == 0 || game->mapHeight == 0 || game->error_code < 0)
		error_free(game, "Error map\n");
	map_copy(input, game);
	//print_map(game);	
}
