/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 14:32:27 by smoreron         ###   ########.fr       */
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
