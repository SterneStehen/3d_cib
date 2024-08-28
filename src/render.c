/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/28 22:12:52 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../include/cub3d.h"


int	execute_raycasting(t_game *game) 
{
  // Инициализация переменных для raycasting
  game->ray.x = 0;

  // Основной цикл по ширине экрана
  while (game->ray.x < game->resolut_width) 
  {
    // Инициализация переменных, связанных с raycasting
    game->ray.flag_hit = 0;
    game->ray.perpwalldist = 0;
    game->ray.cameraX = 2 * game->ray.x / (double)game->resolut_width - 1;
    game->ray.beam_dir_x =
        game->ray.dirX + game->ray.planX * game->ray.cameraX;
    game->ray.beam_dir_y =
        game->ray.dirY + game->ray.planY * game->ray.cameraX;
    game->ray.mapX = (int)game->ray.posX;
    game->ray.mapY = (int)game->ray.posY;
    game->ray.move_speed = 0.1;
    game->ray.rotation_speed = 0.033 * 1.8;

    // Инициализация для расстояний до стороны
    if (game->ray.beam_dir_y == 0)
      game->ray.dist_to_side_x = 0;
    else if (game->ray.beam_dir_x == 0)
      game->ray.dist_to_side_x = 1;
    else
      game->ray.dist_to_side_x =
          sqrt(1 + (game->ray.beam_dir_y * game->ray.beam_dir_y) /
                       (game->ray.beam_dir_x * game->ray.beam_dir_x));

    if (game->ray.beam_dir_x == 0)
      game->ray.dist_to_side_y = 0;
    else if (game->ray.beam_dir_y == 0)
      game->ray.dist_to_side_y = 1;
    else
      game->ray.dist_to_side_y =
          sqrt(1 + (game->ray.beam_dir_x * game->ray.beam_dir_x) /
                       (game->ray.beam_dir_y * game->ray.beam_dir_y));

    // Выполнение шагов raycasting
    draw_wall(game);
    textur_color(game);

    // Сохранение глубины текущего луча
    game->sprite_data.depthBuffer[game->ray.x] = game->ray.perpwalldist;

    // Увеличение индекса луча
    game->ray.x++;
    }
  // Вывод изображения на окно
    mlx_put_image_to_window(game->render_data.mlx_ptr, game->render_data.win,
                          game->render_data.img, 0, 0);
    funk_A_D(game);
    return (0);
}
