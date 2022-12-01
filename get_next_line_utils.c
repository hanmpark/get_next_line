/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:58:18 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/01 11:54:36 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_buffjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	dstsize;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	dstsize = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc((dstsize + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest = ft_strcpy(dest, s1);
	i = ft_strlen(s1);
	free(s1);
	while (i < dstsize)
	{
		dest[i] = *s2;
		s2++;
		i++;
	}
	dest[dstsize] = 0;
	return (dest);
}

int	ft_chars_after_n(char *str)
{
	int	count;

	count = 0;
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		str++;
	while (*str++)
		count++;
	return (count);
}

char	*ft_substr_n(char *str)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	j = ft_chars_after_n(str);
	dst = malloc((j + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	if (str[i] == '\n')
		i++;
	while (str[i])
	{
			*dst = str[i++];
			dst++;
	}
	*dst = 0;
	str[i - j] = 0;
	return (dst - j);
}
