/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:10:24 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/17 21:47:19 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	errmsg(t_data *data, const char *msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	if (data->win)
		mlx_destroy_window(data->mlx_ptr, data->win);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);

	exit(EXIT_FAILURE);
}