# Имя исполняемого файла
NAME := cub3D

# Компилятор и флаги компиляции
CC := gcc
CFLAGS := -Wall -Wextra -Werror -I include

# Директория с исходным кодом и директория для объектных файлов
SRCDIR := src
OBJDIR := obj

# Заголовочные файлы
INCLUDES := -I include

# Автоматическое включение всех файлов .c из папки src
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Путь к библиотекам
LIBFT := ./minilibx-linux/libmlx.a

# Флаги для линковки (для Linux)
LDFLAGS := -Lminilibx-linux -lmlx -lm -lX11 -lXext

# Основные цели
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Правило для компиляции объектных файлов
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# Создание директории для объектных файлов
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Очистка объектных файлов
clean:
	rm -rf $(OBJDIR)

# Полная очистка проекта
fclean: clean
	rm -f $(NAME)

# Пересборка проекта
re: fclean all

# Правило для компиляции библиотеки MiniLibX
$(LIBFT):
	make -C minilibx-linux

.PHONY: all clean fclean re
