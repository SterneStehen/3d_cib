

CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I minilibx_macos


SRCDIR = src
OBJDIR = obj
LIBDIR = minilibx_opengl

SRC = $(SRCDIR)/main.c $(SRCDIR)/parser.c $(SRCDIR)/clean.c $(SRCDIR)/color.c $(SRCDIR)/texture_color.c\
		$(SRCDIR)/draw_wall.c $(SRCDIR)/get_next_util.c $(SRCDIR)/get_next.c $(SRCDIR)/init.c\
		$(SRCDIR)/map.c $(SRCDIR)/move.c $(SRCDIR)/run_mlx.c $(SRCDIR)/texture.c\
		$(SRCDIR)/render.c $(SRCDIR)/init_utils.c $(SRCDIR)/color_utils.c $(SRCDIR)/move_utils.c\
		$(SRCDIR)/map_utils.c $(SRCDIR)/map_utils_2.c $(SRCDIR)/color_utils_2.c $(SRCDIR)/color_parse.c\

OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NAME = cub3D

LIBS = -L$(LIBDIR) -lmlx -framework OpenGL -framework AppKit -framework Cocoa

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re