/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <smoreron@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:50:01 by smoreron          #+#    #+#             */
/*   Updated: 2024/08/19 15:26:13 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char		*ft_subbuff(char *buffer, int begin, int len)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(tmp, buffer);
	i = 0;
	while (tmp[i] != '\0' && i < len)
	{
		buffer[i] = tmp[begin];
		i++;
		begin++;
	}
	buffer[i] = 0;
	free(tmp);
	return (buffer);
}


int			ft_strlen(char *str)
{
	int			ind;

	ind = 0;
	if (!str)
		return (0);
	while (str[ind])
		ind++;
	return (ind);
}

char		*ft_substr(char const *s, unsigned int begin, size_t len)
{
	char	*resul;
	size_t	ind;

	ind = 0;
	resul = malloc(sizeof(char) * (len + 1));
	if (begin < (unsigned int)ft_strlen((char *)s))
	{
		while (s[begin] != '\0' && ind < len)
		{
			resul[ind] = s[begin];
			ind++;
			begin++;
		}
	}
	resul[ind] = '\0';
	return (resul);
}

char		*ft_strjoin(char *str1, char *str2)
{
	char	*resul;
	int		i;
	int		j;

	if (!(resul = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1))))
		return (NULL);
	i = 0;
	while (str1 && str1[i])
	{
		resul[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j])
	{
		resul[i] = str2[j];
		j++;
		i++;
	}
	resul[i] = '\0';
	return (resul);
}

