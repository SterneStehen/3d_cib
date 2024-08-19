/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:10:24 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 14:33:00 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_line_empty(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] != 9 &&  // ASCII для '\t' (табуляция)
			str[index] != 32 && // ASCII для ' ' (пробел)
			str[index] != 10 && // ASCII для '\n' (новая строка)
			str[index] != 13 && // ASCII для '\r' (возврат каретки)
			str[index] != 11 && // ASCII для '\v' (вертикальная табуляция)
			str[index] != 12)   // ASCII для '\f' (переход на новую страницу)
			return (1);
		index++;
	}
	return (0);
}



void	errmsg_simle(const char *msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}