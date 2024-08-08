/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:29 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/08 21:23:41 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}

void init_player(t_data *data)
{
    data->player.posX = 22;
    data->player.posY = 12;
    data->player.dirX = -1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.66;
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
        return (1);
    }

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");

    parse_map(argv[1], &data);
    render(&data);

    mlx_hook(data.win, 17, 0, close_window, &data); // Close window on red cross click
    mlx_loop(data.mlx);

    return (0);
}
