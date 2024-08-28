/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:41:33 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 22:26:47 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



int	run_mlx(t_game *game) {
  // Инициализация позиции и движения
  init_pos_move(game);

  // Инициализация miniLibX
  game->render_data.mlx_ptr = mlx_init();
  if (!game->render_data.mlx_ptr) {
    error_free(game, "Mlx init impossible\n");
  }

  // Определение размера экрана и корректировка разрешения
  int screen_width, screen_height;
  mlx_get_screen_size(game->render_data.mlx_ptr, &screen_width, &screen_height);
  game->resolut_width =
      (game->resolut_width > screen_width) ? screen_width : game->resolut_width;
  game->resolut_height = (game->resolut_height > screen_height)
                             ? screen_height
                             : game->resolut_height;

  // Запуск инициализации текстур
  texture_run(game);

  // Создание нового изображения для отображения
  game->render_data.img = mlx_new_image(
      game->render_data.mlx_ptr, game->resolut_width, game->resolut_height);
  game->render_data.buffer_pix = (int *)mlx_get_data_addr(
      game->render_data.img, &game->render_data.bits_pix,
      &game->render_data.size_line, &game->render_data.byte_order);

  // Выполнение raycasting, если установлен флаг сохранения
  if (game->save == 1) {
    execute_raycasting(game);
  }

  // Создание окна для отображения игры
  game->render_data.win =
      mlx_new_window(game->render_data.mlx_ptr, game->resolut_width,
                     game->resolut_height, "Cub3D");

  // Создание дополнительного изображения для наложения (overlay)
  game->render_data.overlay_image = mlx_new_image(
      game->render_data.mlx_ptr, game->resolut_width, game->resolut_height);
  game->render_data.overlay_buffer = (int *)mlx_get_data_addr(
      game->render_data.overlay_image, &game->render_data.bits_pix,
      &game->render_data.size_line, &game->render_data.byte_order);

  // Установка обработчиков событий
  mlx_hook(game->render_data.win, 33, 1L << 17, destroy,
           game); // Обработчик выхода
  mlx_hook(game->render_data.win, 2, 1L << 0, input_keyboard,
           game); // Обработчик нажатия клавиш
  mlx_loop_hook(game->render_data.mlx_ptr, execute_raycasting,
                game); // Основной цикл raycasting
  mlx_hook(game->render_data.win, 3, 1L << 1, press_key,
           game); // Обработчик отпускания клавиш

  // Запуск основного цикла miniLibX
  mlx_loop(game->render_data.mlx_ptr);

  return (0);
}