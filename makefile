NAME := cub3D

CC := gcc
CFLAGS := -Wall -Wextra -Werror -I include

SRCDIR := src
OBJDIR := obj

INCLUDES := -I include

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Путь к библиотекам
LIBFT := ./minilibx-linux/libmlx.a

# Определяем операционную систему
UNAME := $(shell uname)

# Флаги для линковки (для Linux)
ifeq ($(UNAME), Linux)
	LDFLAGS := -Lminilibx-linux -lmlx -lm -lX11 -lXext -lbsd
endif

# Флаги для линковки (для macOS)
ifeq ($(UNAME), Darwin)
	LDFLAGS := -Lminilibx_macos -lmlx -lm
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(LIBFT):
ifeq ($(UNAME), Linux)
	make -C minilibx-linux
endif

ifeq ($(UNAME), Darwin)
	make -C minilibx_macos
endif

.PHONY: all clean fclean re
