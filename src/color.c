/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 23:14:55 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "../include/cub3d.h"


// int	textur_color(t_game *game)
// {
// 	int	j;
// 	int	i;

// 	j = -1;
// 	game->ray.finish_draw_px = game->resolut_height - game->ray.begin_draw_px;
// 	i = game->ray.finish_draw_px;
// 	// Окрашивание потолка
// 	while (++j < game->ray.begin_draw_px)
// 		game->render_data.buffer_pix[j * game->render_data.size_line / 4
// 			+ game->ray.x] = game->ceiling_color;
// 	// Инициализация текстуры перед началом отрисовки
// 	if (game->ray.collision_side == 0 && game->ray.beam_dir_x < 0)
// 		game->material_data.dir = 0;
// 	if (game->ray.collision_side == 0 && game->ray.beam_dir_x >= 0)
// 		game->material_data.dir = 1;
// 	if (game->ray.collision_side == 1 && game->ray.beam_dir_y < 0)
// 		game->material_data.dir = 2;
// 	if (game->ray.collision_side == 1 && game->ray.beam_dir_y >= 0)
// 		game->material_data.dir = 3;
// 	if (game->ray.collision_side == 0)
// 		game->material_data.wallHitX = game->ray.posY + game->ray.perpwalldist
// 			* game->ray.beam_dir_y;
// 	else
// 		game->material_data.wallHitX = game->ray.posX + game->ray.perpwalldist
// 			* game->ray.beam_dir_x;
// 	game->material_data.wallHitX -= floor((game->material_data.wallHitX));
// 	game->material_data.step = 1.0 * game->surfaces[0].win_height
// 		/ game->ray.wall_height_px;
// 	game->material_data.coordX = (int)(game->material_data.wallHitX
// 			* (double)game->surfaces[game->material_data.dir].win_width);
// 	// Учет направления для текстурирования
// 	if (game->ray.collision_side == 0 && game->ray.beam_dir_x > 0)
// 		game->material_data.coordX = game->surfaces[game->material_data.dir].win_width
// 			- game->material_data.coordX - 1;
// 	if (game->ray.collision_side == 1 && game->ray.beam_dir_y < 0)
// 		game->material_data.coordX = game->surfaces[game->material_data.dir].win_width
// 			- game->material_data.coordX - 1;
// 	// Инициализация начальной позиции для текстурирования
// 	game->material_data.position = (game->ray.begin_draw_px
// 			- game->resolut_height / 2 + game->ray.wall_height_px / 2)
// 		* game->material_data.step;
// 	// Текстурирование стены
// 	j = game->ray.begin_draw_px - 1;
// 	while (++j <= game->ray.finish_draw_px)
// 	{
// 		game->material_data.coordY = (int)game->material_data.position & (game->surfaces[game->material_data.dir].win_height
// 				- 1);
// 		game->material_data.position += game->material_data.step;
// 		if (j < game->resolut_height && game->ray.x < game->resolut_width)
// 			game->render_data.buffer_pix[j * game->render_data.size_line / 4
// 				+ game->ray.x] = game->surfaces[game->material_data.dir].buffer_pix[game->material_data.coordY
// 				* game->surfaces[game->material_data.dir].size_line / 4
// 				+ game->material_data.coordX];
// 	}
// 	// Окрашивание пола
// 	j = i;
// 	while (++j < game->resolut_height)
// 		game->render_data.buffer_pix[j * game->render_data.size_line / 4
// 			+ game->ray.x] = game->floor_color;
// 	return (0);
// }

#include <stdio.h> // Не забудьте подключить stdio.h для использования printf

int add_alpha_channel(int color) {
    // Добавляем альфа-канал, сдвигая 0xFF на старшие 8 бит и объединяя его с цветом
    int result = (0xFF << 24) | color;
    printf("Adding alpha channel: Original color: %d, Resulting ARGB color: %d\n", color, result);
    return result;
}

int textur_color(t_game *game) {
    int j;
    int i;

    // Инициализируем значения
    j = -1;
    game->ray.finish_draw_px = game->resolut_height - game->ray.begin_draw_px;
    i = game->ray.finish_draw_px;

    // Преобразуем цвета в формат ARGB и выводим значения для проверки
    int ceiling_color_argb = add_alpha_channel(game->ceiling_color);
    int floor_color_argb = add_alpha_channel(game->floor_color);
    printf("Ceiling color ARGB: %d, Floor color ARGB: %d\n", ceiling_color_argb, floor_color_argb);

    // Окрашивание потолка
    while (++j < game->ray.begin_draw_px) {
        game->render_data.buffer_pix[j * game->render_data.size_line / 4 + game->ray.x] = ceiling_color_argb;
    }

    // Инициализация текстуры перед началом отрисовки
    if (game->ray.collision_side == 0 && game->ray.beam_dir_x < 0)
        game->material_data.dir = 0;
    if (game->ray.collision_side == 0 && game->ray.beam_dir_x >= 0)
        game->material_data.dir = 1;
    if (game->ray.collision_side == 1 && game->ray.beam_dir_y < 0)
        game->material_data.dir = 2;
    if (game->ray.collision_side == 1 && game->ray.beam_dir_y >= 0)
        game->material_data.dir = 3;

    // Выводим значения направления и пересечения стены
    printf("Collision side: %d, Beam direction X: %f, Beam direction Y: %f\n", game->ray.collision_side, game->ray.beam_dir_x, game->ray.beam_dir_y);
    printf("Texture direction: %d\n", game->material_data.dir);

    if (game->ray.collision_side == 0)
        game->material_data.wallHitX = game->ray.posY + game->ray.perpwalldist * game->ray.beam_dir_y;
    else
        game->material_data.wallHitX = game->ray.posX + game->ray.perpwalldist * game->ray.beam_dir_x;

    game->material_data.wallHitX -= floor(game->material_data.wallHitX);
    printf("Wall hit X after adjustment: %f\n", game->material_data.wallHitX);

    game->material_data.step = 1.0 * game->surfaces[0].win_height / game->ray.wall_height_px;
    game->material_data.coordX = (int)(game->material_data.wallHitX * (double)game->surfaces[game->material_data.dir].win_width);
    printf("Texture step: %f, CoordX: %d\n", game->material_data.step, game->material_data.coordX);

    // Учет направления для текстурирования
    if (game->ray.collision_side == 0 && game->ray.beam_dir_x > 0)
        game->material_data.coordX = game->surfaces[game->material_data.dir].win_width - game->material_data.coordX - 1;
    if (game->ray.collision_side == 1 && game->ray.beam_dir_y < 0)
        game->material_data.coordX = game->surfaces[game->material_data.dir].win_width - game->material_data.coordX - 1;

    // Инициализация начальной позиции для текстурирования
    game->material_data.position = (game->ray.begin_draw_px - game->resolut_height / 2 + game->ray.wall_height_px / 2) * game->material_data.step;
    printf("Initial texture position: %f\n", game->material_data.position);

    // Текстурирование стены
    j = game->ray.begin_draw_px - 1;
    while (++j <= game->ray.finish_draw_px) {
        game->material_data.coordY = (int)game->material_data.position & (game->surfaces[game->material_data.dir].win_height - 1);
        game->material_data.position += game->material_data.step;
        if (j < game->resolut_height && game->ray.x < game->resolut_width)
            game->render_data.buffer_pix[j * game->render_data.size_line / 4 + game->ray.x] = game->surfaces[game->material_data.dir].buffer_pix[game->material_data.coordY * game->surfaces[game->material_data.dir].size_line / 4 + game->material_data.coordX];
    }

    // Окрашивание пола
    j = i;
    while (++j < game->resolut_height) {
        game->render_data.buffer_pix[j * game->render_data.size_line / 4 + game->ray.x] = floor_color_argb;
    }

    printf("Finished rendering column at x = %d\n", game->ray.x);
    return (0);
}


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
	

	// int r = (color >> 16) & 0xFF;
	// int g = (color >> 8) & 0xFF;
	// int b = color & 0xFF;

	ft_free_split(split_line);
	
}

