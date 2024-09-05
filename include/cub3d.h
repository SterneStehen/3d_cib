/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:02:06 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/05 01:09:33 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// for linux
// # include "../minilibx-linux/mlx.h"

// for MacOs:
//# include "../libft/libft.h"
# include "../minilibx_opengl/mlx.h"
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
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

typedef struct s_material
{
	int			dir;
	double		wall_hit_x;
	int			coord_x;
	int			coord_y;
	double		step;
	double		position;
}				t_material;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
	double		beam_dir_x;
	double		beam_dir_y;
	double		camera_x;
	int			map_x;
	int			map_y;
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
	int			map_height;
	int			map_width;
	int			pos_xp;
	int			pos_yp;
	double		pdirx;
	double		pdir_y;
	int			save;
	int			viewport_width;
	int			viewport_height;
	int			error_code;
	int			is_multiplayer;
	int			empty_line;
	int			inside_map;
	int			total_sum;
	int			invalid_chars;
	int			counter1;
	int			texture_audit[7];
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite_texture;
	char		**level_map;
	char		start_dir;
	t_data		surfaces[4];
	t_data		render_data;
	t_player	ray;
	t_material	material_data;
}				t_game;

// init
void			game_init(t_game *game);
int				init_start_position(char c, t_game *data, int i, int j);

// util
// int	ft_strcmp(char *s1, char *s2);
int				ft_strcmp(const char *s1, const char *s2);

// parce
void			parsing(char *input, t_game *game);
void			print_game_info(t_game *game);
int				*parse_map_line(char *line, int width);
int				calcul_arr(char **array);

// color
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b);
void			set_color(char *line, t_game *game);
char			**ft_split(char const *s, char c);
void			ft_free_split(char **split);
int				ft_array_len(char **array);
int				ft_word_count(char const *str, char c);
int				find_start(const char *s, char c, int i);
void			check_color_range(t_game *game, int r, int g, int b);

// map
void			set_map_dimensions(char *line, t_game *game);
int				audit_map(char *str, t_game *game);
int				map_copy(char *input, t_game *game);
int				map_duble(char *line, t_game *data);
int				parse_map(char *input, t_game *game);
int				wall_check(t_game *game);

// texture
void			set_texture(char *line, t_game *game);

// util
int				is_line_empty(char *str);
// void	errmsg(t_data *data, const char *msg);

// clean
void			error_free(t_game *data, char *str);
int				destroy(t_game *game);
int				close_win(t_game *game);
// get_next
int				get_next_line(int fd, char **line);
int				ft_strlen(char *str);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_subbuff(char *buff, int start, int len);

// sprit

void			init_pos_move(t_game *game);
void			sprite_start(t_game *game);

// mlx
int				run_mlx(t_game *game);
int				execute_raycasting(t_game *recup);
void			texture_run(t_game *game);
void			draw_wall(t_game *game);
int				textur_color(t_game *game);

// move
int				press_key(int input, t_game *game);
int				input_keyboard(int sense, t_game *game);
void			funk_a_d(t_game *game);
void			funk_w_s(t_game *game);
void			funk_left_right(t_game *game);
void			swap_images(t_game *game);

#endif
