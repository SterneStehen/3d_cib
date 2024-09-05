/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:50:01 by smoreron          #+#    #+#             */
/*   Updated: 2024/09/04 22:53:09 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_subbuff(char *buffer, int begin, int len)
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

int	ft_strlen(char *str)
{
	int	ind;

	ind = 0;
	if (!str)
		return (0);
	while (str[ind])
		ind++;
	return (ind);
}

char	*ft_substr(char const *s, unsigned int begin, size_t len)
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

char	*ft_strjoin(char *str1, char *str2)
{
	char	*resul;
	int		i;
	int		j;

	resul = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!resul)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
