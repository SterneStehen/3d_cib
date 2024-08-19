/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:05:09 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 14:25:08 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/cub3d.h"

void free_textures(t_game *data)
{
    if (data->north_texture)
        free(data->north_texture);
    if (data->south_texture)
        free(data->south_texture);
    if (data->west_texture)
        free(data->west_texture);
    if (data->east_texture)
        free(data->east_texture);
    if (data->sprite_texture)
        free(data->sprite_texture);
}

void free_map(t_game *data)
{
    int i;

    if (data->level_map)
    {
        i = 0;
        while (i < data->mapHeight)
        {
            if (data->level_map[i])
                free(data->level_map[i]);
            i++;
        }
        free(data->level_map);
    }
}


void free_struct(t_game *data)
{
    free_textures(data);
    free_map(data);
}


void	error_free(t_game *data, char *str)
{
    

    write(1, "Error\n", 6);
    write(1, str, ft_strlen(str));


    free_struct(data);


    exit(0);
}
