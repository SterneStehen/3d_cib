/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:02:06 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/29 00:42:50 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//for linux
# include "../minilibx-linux/mlx.h"

// for MacOs:
// # include <../minilibx_opengl/mlx.h> 
// # include <OpenGL/gl.h>
// # include <OpenGL/glu.h> 

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define FOV 60
# define MAX_BUFFER_SIZE 1920

# define BUFFER_SIZE 4096



typedef struct s_point2D
{
	double		x;
	double		y;
} е_point2D;

typedef struct s_material
{
	int			dir;
	double		wallHitX;
	int			coordX;
	int			coordY;
	double		step;
	double		position;
}				t_material;

typedef struct s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planX;
	double		planY;
	double		beam_dir_x;
	double		beam_dir_y;
	double		cameraX;
	int			mapX;
	int			mapY;
	double		grid_x;
	double		grid_y;
	double		dist_to_side_x;
	double		dist_to_side_y;
	int			step_x;
	int			step_y;
	int			flag_hit;
	int			collision_side;
	double		perpwalldist;
	int			wall_height_px;
	int			begin_draw_px;
	int			finish_draw_px;
	double		move_speed;
	double		rotation_speed;
	int			x;
	int			wall_texture;
}				t_player;

typedef struct s_sprite
{
	int			count;
	int			projectedX;
	int			entityHeight;
	int			startX;
	int			startY;
	int			endY;
	int			endX;
	int			width;
	int			*renderOrder;
	double		*distance;
	double		entityPosX;
	double		entityPosY;
	double		inverseDeterminant;
	double		transX;
	double		transY;
	double		*depthBuffer;
}				t_sprite;


typedef struct s_data
{
	int			bits_pix;
	int			size_line;
	int			byte_order;
	int			move_ahed;
	int			move_back;
	int			move_left;
	int			move_right;
	int			left_rot;
	int			right_rotet;
	int			minimap_scale;
	int			win_width;
	int			win_height;
	int			*buffer_pix;
	int			*overlay_buffer;
	void		*overlay_image;
	void		*mlx_ptr;
	void		*win;
	void		*img;
}				t_data;

typedef struct s_game
{
	int			resolut_width;
	int			resolut_height;
	int			i;
	int			floor_color;
	int			ceiling_color;
	int			mapHeight;
	int			mapWidth;
	int			posXp;
	int			posYp;
	double		pdirx;
	double		pdiry;
	double 		pplanex;
	double		pplaney;
	int			save;
	int			viewport_width;
	int			viewport_height;
	int			error_code;
	int			is_multiplayer;
	int			empty_line;
	int			inside_map;
	int			total_sum;
	int			invalid_chars;
	int counter1;
	int counter2;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite_texture;
	char		**level_map;
	char		start_dir;
	t_data		surfaces[5];
	t_data		render_data;
	t_player	ray;
	t_sprite	sprite_data;
	е_point2D	*sprites_pos;
	t_material material_data;
}			t_game;


//init 
void	game_init(t_game *game);
int	init_start_posicion(char c, t_game *data, int i, int j);
// parce
void	parsing(char *input, t_game *game);
void	print_game_info(t_game *game);
int *parse_map_line(char *line, int width);


// resolut
int	set_resolution(char *str, t_game *game);
int	is_char_in_str(char *str, char c);

//color 
void	set_color(char *line, t_game *game);
char	**ft_split(char const *s, char c);

//map
void	set_map_dimensions(char *line, t_game *game);
int	audit_map(char *str, t_game *game);
int	map_copy(char *input, t_game *game);
int	map_duble(char *line, t_game *data);

//texture
void set_texture(char *line, t_game *game);

//util
int	is_line_empty(char *str);
//void	errmsg(t_data *data, const char *msg);

//clean
void	error_free(t_game *data, char *str);
int	destroy(t_game *game);


//get_next
int		get_next_line(int fd, char **line);
int			ft_strlen(char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_subbuff(char *buff, int start, int len);

//sprit 

void	init_pos_move(t_game *game);
void	sprite_start(t_game *game);

//mlx 
int	run_mlx(t_game *game);
int	execute_raycasting(t_game *recup);
void	texture_run(t_game *game);
void	draw_wall(t_game *game);
int	textur_color(t_game *game);


//move
int	press_key(int input, t_game *game);
void funk_A_D(t_game *game);
int	input_keyboard(int sense, t_game *game);

#endif
