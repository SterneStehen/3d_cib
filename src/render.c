/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/10 18:05:09 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void clear_image(t_data *data)
{
    int i;
    int size = WIN_WIDTH * WIN_HEIGHT;

    for (i = 0; i < size; i++)
        data->img.data[i] = 0x000000; // Clear to black or any default background color
}

void draw_floor_and_ceiling(t_data *data)
{
    int y;
    int floorColor = data->floorColor;
    int ceilingColor = data->ceilingColor;

    for (y = 0; y < WIN_HEIGHT / 2; y++)
    {
        int pixelIndex = y * WIN_WIDTH;
        for (int x = 0; x < WIN_WIDTH; x++)
        {
            data->img.data[pixelIndex + x] = ceilingColor; // Draw ceiling
        }
    }

    for (y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
    {
        int pixelIndex = y * WIN_WIDTH;
        for (int x = 0; x < WIN_WIDTH; x++)
        {
            data->img.data[pixelIndex + x] = floorColor; // Draw floor
        }
    }
}

void render(t_data *data)
{
    int w = WIN_WIDTH;
    int h = WIN_HEIGHT;
    double posX = data->player.posX;
    double posY = data->player.posY;
    double dirX = data->player.dirX;
    double dirY = data->player.dirY;
    double planeX = data->player.planeX;
    double planeY = data->player.planeY;

    clear_image(data);
    draw_floor_and_ceiling(data);

    for (int x = 0; x < w; x++)
    {
        double cameraX = 2 * x / (double)w - 1; // x-coordinate in camera space
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (data->worldMap[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(h / perpWallDist);

        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h) drawEnd = h - 1;

        int color;
        switch (data->worldMap[mapX][mapY])
        {
            case 1:  color = 0xFF0000;  break;
            case 2:  color = 0x00FF00;  break;
            case 3:  color = 0x0000FF;  break;
            case 4:  color = 0xFFFFFF;  break;
            default: color = 0xFFFF00;  break;
        }

        if (side == 1) color = color / 2;

        draw_vertical_line(data, x, drawStart, drawEnd, color);
    }

    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
