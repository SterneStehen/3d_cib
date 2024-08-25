/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: puiucorina <puiucorina@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/21 12:01:22 by puiucorina       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	clear_image(t_data *data)
// {
// 	int	i;
// 	int	size;

// 	size = WIN_WIDTH * WIN_HEIGHT;
// 	for (i = 0; i < size; i++)
// 		data->img.data[i] = 0x000000;
// 			// Clear to black or any default background color
// }

// void	draw_floor_and_ceiling(t_data *data)
// {
// 	int	y;
// 	int	floorColor;
// 	int	ceilingColor;
// 	int	pixelIndex;
// 	int	pixelIndex;

// 	floorColor = data->floorColor;
// 	ceilingColor = data->ceilingColor;
// 	for (y = 0; y < WIN_HEIGHT / 2; y++)
// 	{
// 		pixelIndex = y * WIN_WIDTH;
// 		for (int x = 0; x < WIN_WIDTH; x++)
// 		{
// 			data->img.data[pixelIndex + x] = ceilingColor; // Draw ceiling
// 		}
// 	}
// 	for (y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
// 	{
// 		pixelIndex = y * WIN_WIDTH;
// 		for (int x = 0; x < WIN_WIDTH; x++)
// 		{
// 			data->img.data[pixelIndex + x] = floorColor; // Draw floor
// 		}
// 	}
// }

// void	render(t_data *data)
// {
// 	int		w;
// 	int		h;
// 	double	posX;
// 	double	posY;
// 	double	dirX;
// 	double	dirY;
// 	double	planeX;
// 	double	planeY;
// 	double	rayDirX;
// 	double	rayDirY;
// 	int		mapX;
// 	int		mapY;
// 		double sideDistX;
// 		double sideDistY;
// 	double	deltaDistX;
// 	double	deltaDistY;
// 		double perpWallDist;
// 		int stepX;
// 		int stepY;
// 	int		hit;
// 		int side;
// 	int		lineHeight;
// 	int		drawStart;
// 	int		drawEnd;
// 		int color;

// 	w = WIN_WIDTH;
// 	h = WIN_HEIGHT;
// 	posX = data->player.posX;
// 	posY = data->player.posY;
// 	dirX = data->player.dirX;
// 	dirY = data->player.dirY;
// 	planeX = data->player.planeX;
// 	planeY = data->player.planeY;
// 	clear_image(data);
// 	draw_floor_and_ceiling(data);
// 	for (int x = 0; x < w; x++)
// 	{
// 		double cameraX = 2 * x / (double)w - 1; // x-coordinate in camera space
// 		rayDirX = dirX + planeX * cameraX;
// 		rayDirY = dirY + planeY * cameraX;
// 		mapX = (int)posX;
// 		mapY = (int)posY;
// 		deltaDistX = fabs(1 / rayDirX);
// 		deltaDistY = fabs(1 / rayDirY);
// 		hit = 0;
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (posX - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
// 		}
// 		while (hit == 0)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if (data->worldMap[mapX][mapY] > 0)
// 				hit = 1;
// 		}
// 		if (side == 0)
// 			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
// 		else
// 			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
// 		lineHeight = (int)(h / perpWallDist);
// 		drawStart = -lineHeight / 2 + h / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		drawEnd = lineHeight / 2 + h / 2;
// 		if (drawEnd >= h)
// 			drawEnd = h - 1;
// 		switch (data->worldMap[mapX][mapY])
// 		{
// 		case 1:
// 			color = 0xFF0000;
// 			break ;
// 		case 2:
// 			color = 0x00FF00;
// 			break ;
// 		case 3:
// 			color = 0x0000FF;
// 			break ;
// 		case 4:
// 			color = 0xFFFFFF;
// 			break ;
// 		default:
// 			color = 0xFFFF00;
// 			break ;
// 		}
// 		if (side == 1)
// 			color = color / 2;
// 		draw_vertical_line(data, x, drawStart, drawEnd, color);
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.img_ptr, 0, 0);
// }

void raycast(t_game *game)
{
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)WIN_HEIGHT - 1; // X-coordinate in camera space
        double rayDirX = game->pdirx + game->pplanex * cameraX;
        double rayDirY = game->pdiry + game->pplaney * cameraX;

        // Which box of the map we're in
        int mapX = (int)game->posXp;
        int mapY = (int)game->posYp;

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // Direction to move in the map grid
        int stepX;
        int stepY;

        int hit = 0; // Has the ray hit a wall?
        int side; // Was the wall hit a NS or a EW wall?

        // Calculate step and initial sideDist
        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->posXp - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posXp) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->posXp - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posXp) * deltaDistY;
        }

        // Perform DDA
        while(hit == 0)
        {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if(sideDistX < sideDistY)
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
            // Check if ray has hit a wall
            if(game->level_map[mapX][mapY] > 0) hit = 1;
        }

        // Calculate distance to the point of impact
        if(side == 0) perpWallDist = (mapX - game->posXp + (1 - stepX) / 2) / rayDirX;
        else          perpWallDist = (mapY - game->posYp + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        // Choose wall color based on hit side
        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

        // Draw the ceiling, wall, and floor for this vertical stripe
        drawLine(x, 0, drawStart, 0x87CEEB);  // Sky blue ceiling
        drawLine(x, drawStart, drawEnd, color);  // Wall
        drawLine(x, drawEnd, WIN_HEIGHT, 0x228B22);  // Forest green floor
    }
}