/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:02:06 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/17 23:17:14 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

typedef struct s_point2D
{
	double		x;
	double		y;
} е_point2D;


typedef struct  s_img {
    void        *img_ptr;
    int         *data;
    
    int         bpp;
    int         size_l;
    int         endian;
}               t_img;

typedef struct  s_player {
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;
}               t_player;

typedef struct  s_data {
    void        *mlx_ptr;
    void        *win;
    t_img       img;
    t_player    player;
    int         **worldMap;
    int         mapWidth;
    int         mapHeight;
}               t_data;


typedef struct s_game
{
	int			res_width;
	int			res_height;
	int			i;
	int			floor_color;
	int			ceiling_color;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite_texture;
	int			mapHeight;
	int			mapWidth;
    е_point2D   *sprites_pos;
}				t_game;

// Function prototypes
void    parse_map(const char *file, t_data *data);
void    render(t_data *data);
void    draw_vertical_line(t_data *data, int x, int start, int end, int color);

#endif
