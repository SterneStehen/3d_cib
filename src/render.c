/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:13 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/29 01:31:11 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../include/cub3d.h"

int execute_raycasting(t_game *game) 
{
    // Initialize the variable for the x-coordinate of the ray
    game->ray.x = 0;

    // Main loop iterating over the screen width to process each vertical stripe
    while (game->ray.x < game->resolut_width) 
    {
        // Resetting the hit flag and perpendicular wall distance for each ray
        game->ray.flag_hit = 0;    // Indicates whether a wall has been hit
        game->ray.perpwalldist = 0; // Distance to the wall hit

        // Calculating the x-coordinate on the camera plane
        game->ray.cameraX = 2 * game->ray.x / (double)game->resolut_width - 1;

        // Calculating the direction vector of the ray based on camera plane and cameraX
        game->ray.beam_dir_x = game->ray.dirX + game->ray.planX * game->ray.cameraX;
        game->ray.beam_dir_y = game->ray.dirY + game->ray.planY * game->ray.cameraX;

        // Determining the player's position on the map grid
        game->ray.mapX = (int)game->ray.posX; // Current x position on the map
        game->ray.mapY = (int)game->ray.posY; // Current y position on the map

        // Setting the movement and rotation speed
        game->ray.move_speed = 0.1;             // Speed at which the player moves
        game->ray.rotation_speed = 0.033 * 1.8; // Speed at which the player rotates

        // Calculate the distance to the side of the next grid line in x-direction
        if (game->ray.beam_dir_y == 0)
            game->ray.dist_to_side_x = 0;
        else if (game->ray.beam_dir_x == 0)
            game->ray.dist_to_side_x = 1;
        else
            game->ray.dist_to_side_x = sqrt(1 + (game->ray.beam_dir_y * game->ray.beam_dir_y) /
                                              (game->ray.beam_dir_x * game->ray.beam_dir_x));

        // Calculate the distance to the side of the next grid line in y-direction
        if (game->ray.beam_dir_x == 0)
            game->ray.dist_to_side_y = 0;
        else if (game->ray.beam_dir_y == 0)
            game->ray.dist_to_side_y = 1;
        else
            game->ray.dist_to_side_y = sqrt(1 + (game->ray.beam_dir_x * game->ray.beam_dir_x) /
                                              (game->ray.beam_dir_y * game->ray.beam_dir_y));

        // Function call to calculate the ray's path and draw the wall
        draw_wall(game);

        // Function call to apply textures to the walls based on their coordinates
        textur_color(game);

        // Save the distance to the wall hit for the current ray, useful for depth comparisons
        // game->sprite_data.depthBuffer[game->ray.x] = game->ray.perpwalldist;

        // Move to the next ray in the x direction
        game->ray.x++;
    }

    // Display the rendered image on the window
    mlx_put_image_to_window(game->render_data.mlx_ptr, game->render_data.win,
                            game->render_data.img, 0, 0);

    // Handle player movements: forward/backward, left/right, and rotation
    funk_W_S(game);          // Process forward (W) and backward (S) movement
    funk_A_D(game);          // Process left (A) and right (D) strafe movement
    funk_left_right(game);   // Process left/right rotation

    // Swap the rendering buffers to avoid flickering and ensure smooth animation
    swap_images(game);

    return (0); // Return 0 indicating the function executed successfully
}
