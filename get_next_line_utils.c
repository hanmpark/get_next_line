/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:46:43 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/02 19:44:25 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_bufferjoin(char *dest, char *src)
{
	char	*joined;
	int		fulllen;
	int		i;

	i = 0;
	fulllen = ft_strlen(dest) + ft_strlen(src);
	joined = malloc((fulllen + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (dest[i])
		*joined++ = dest[i++];
	free(dest);
	i = 0;
	while (src[i])
		*joined++ = src[i++];
	*joined = 0;
	return (joined - fulllen);
}

char	*ft_linetrim(char *str)
{
	char	*tstr;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i + len])
		len++;
	tstr = malloc((len + 1) * sizeof(char));
	if (!tstr)
		return (NULL);
	while (str[i])
		*tstr++ = str[i++];
	*tstr = 0;
	str[i - len] = 0;
	return (tstr - len);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*tb;
	size_t	i;

	if (count > 4294967295)
		return (NULL);
	i = count * size;
	tb = malloc(i);
	if (!tb)
		return (NULL);
	while (i)
	{
		tb[i] = 0;
		i--;
	}
	return (tb);
}
