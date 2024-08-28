/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 16:29:34 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void drawLine(t_data *data, int x, int startY, int endY, int color)
{

    if (startY < 0) startY = 0;
    if (endY >= data->win_height) endY = data->win_height - 1;

    if (x < 0 || x >= data->win_width)
        return;

    for (int y = startY; y <= endY; y++)
    {
        data->buffer_pix[y * data->win_width + x] = color;
    }
}

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
        drawLine(&game->render_data, x, 0, drawStart, 0x87CEEB);  // Sky blue ceiling
        drawLine(&game->render_data, x, drawStart, drawEnd, color);  // Wall
        drawLine(&game->render_data, x, drawEnd, WIN_HEIGHT, 0x228B22);  // Forest green floor
    }
}