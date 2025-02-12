/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:01:29 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/05 12:14:24 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_input(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf("Usage: ./cub3D map.cub\n");
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strcmp(&argv[1][len - 4], ".cub") != 0)
	{
		printf("Invalid map name. The file must have a '.cub' extension.\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (check_input(argc, argv) != 1)
		return (0);
	game_init(&game);
	parsing(argv[1], &game);
	run_mlx(&game);
	error_free(&game, "all pass\n");
	return (0);
}

	// system("leaks cub3D");