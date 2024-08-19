/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:40:15 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 13:48:30 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void set_texture(char *line, t_game *game)
{
    if (strncmp(line, "NO ", 3) == 0) 
    {
        game->north_texture = strdup(line + 3);
        if (!game->north_texture)
            error_free(game, "Memory allocation error for north texture\n");
    }
    else if (strncmp(line, "SO ", 3) == 0) 
    {
        game->south_texture = strdup(line + 3);
        if (!game->south_texture)
            error_free(game, "Memory allocation error for south texture\n");
    }
    else if (strncmp(line, "EA ", 3) == 0) 
    {
        game->east_texture = strdup(line + 3);
        if (!game->east_texture)
            error_free(game, "Memory allocation error for east texture\n");
    }
    else if (strncmp(line, "WE ", 3) == 0)  
    {
        game->west_texture = strdup(line + 3);
        if (!game->west_texture)
            error_free(game, "Memory allocation error for west texture\n");
    }
    else if (strncmp(line, "S ", 2) == 0)  
    {
        game->sprite_texture = strdup(line + 2);
        if (!game->sprite_texture)
            error_free(game, "Memory allocation error for sprite texture\n");
    }
}
