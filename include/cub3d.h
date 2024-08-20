/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:02:06 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/20 16:27:58 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//for linux
//# include "../minilibx-linux/mlx.h"

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

# define BUFFER_SIZE 4096



typedef struct s_data
{

	int		win_width;
	int		win_height;
	int		*buffer_pix;
	int		*overlay_buffer;
	void	*overlay_image;
	void	*mlx_ptr;
	void	*win;
	void	*img;
}			t_data;

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
}			t_game;


//init 
void	ft_init_game(t_game *game);
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
void	errmsg(t_data *data, const char *msg);

//clean
void	error_free(t_game *data, char *str);


//get_next
int		get_next_line(int fd, char **line, t_game *game);
int			ft_strlen(char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_subbuff(char *buff, int start, int len);

#endif
