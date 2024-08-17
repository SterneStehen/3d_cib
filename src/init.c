/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:04 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/17 21:47:19 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_data *data)
{
    // Set player initial position and direction
    data->player.posX = 22.0;  // Example starting position X
    data->player.posY = 12.0;  // Example starting position Y
    data->player.dirX = -1.0;  // Facing West
    data->player.dirY = 0.0;   // No vertical component in direction
    data->player.planeX = 0.0; 
    data->player.planeY = 0.66; // Camera plane perpendicular to direction
}

void init_window(t_data *data)
{
    // Initialize the window using MiniLibX
    data->mlx_ptr = mlx_init();
    if (data->mlx_ptr == NULL)
    {
        perror("Error initializing MLX");
        exit(1);
    }

    data->win = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (data->win == NULL)
    {
        perror("Error creating window");
        exit(1);
    }
}

void init_image(t_data *data)
{
    // Initialize the image buffer
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    if (data->img.img_ptr == NULL)
    {
        perror("Error creating image");
        exit(1);
    }

    data->img.data = (int *)mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.size_l, &data->img.endian);
    if (data->img.data == NULL)
    {
        perror("Error getting image data address");
        exit(1);
    }
}

void init_map(t_data *data, const char *map_file)
{
    // Parse the map file to initialize the world map and other settings
    parse_map(map_file, data);
}

void init_game(t_data *data, const char *map_file)
{
    // Call the initialization functions
    init_player(data);
    init_window(data);
    init_image(data);
    init_map(data, map_file);
}
