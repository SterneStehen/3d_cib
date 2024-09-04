# NAME := cub3D

# CC := cc
# CFLAGS := -Wall -Wextra  -I include -I minilibx_macos

# SRCDIR := src
# OBJDIR := obj
# FRAMEWORKS =  -lglfw -framework Cocoa -framework OpenGL -framework IOKit
# INCLUDES := -I include

# SRCS := $(wildcard $(SRCDIR)/*.c)
# OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# # Путь к библиотекам
# # LIBFT := ./minilibx-linux/libmlx.a

# # Определяем операционную систему
# # UNAME := $(shell uname)

# # Флаги для линковки (для Linux)
# # ifeq ($(UNAME), Linux)
# # 	LDFLAGS := -Lminilibx-linux -lmlx -lm -lX11 -lXext -lbsd
# # endif

# # # Флаги для линковки (для macOS)
# # ifeq ($(UNAME), Darwin)
# # LDFLAGS := -Lminilibx_macos -lmlx -lm
# # endif

# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(FRAMEWORKS) -o $@ $^ $(LDFLAGS) 

# $(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
# 	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

# clean:
# 	rm -rf $(OBJDIR)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# # $(LIBFT):
# # ifeq ($(UNAME), Linux)
# # 	make -C minilibx-linux
# # endif

# # ifeq ($(UNAME), Darwin)
# 	make -C minilibx_macos
# # endif

# .PHONY: all clean fclean re



CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I minilibx_macos


SRCDIR = src
OBJDIR = obj
LIBDIR = minilibx_opengl

SRC = $(SRCDIR)/main.c $(SRCDIR)/parser.c $(SRCDIR)/clean.c $(SRCDIR)/color.c $(SRCDIR)/texture_color.c\
		$(SRCDIR)/draw_wall.c $(SRCDIR)/get_next_util.c $(SRCDIR)/get_next.c $(SRCDIR)/init.c\
		$(SRCDIR)/map.c $(SRCDIR)/move.c $(SRCDIR)/run_mlx.c $(SRCDIR)/texture.c\
		$(SRCDIR)/render.c $(SRCDIR)/init_utils.c $(SRCDIR)/color_utils.c $(SRCDIR)/move_utils.c\

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