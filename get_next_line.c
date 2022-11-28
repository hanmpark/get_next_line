/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/11/28 13:58:47 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_countc(char *str)
{
	int	count;

	count = 0;
	while (str[count] && str[count] != '\n')
		count++;
	return (count);
}

char	*ft_strncpy(char *s, char *buf, size_t len)
{
	while (*buf && len--)
	{
		*s = *buf;
		buf++;
	}
	*s = '\0';
	return (s);
}

char	*get_next_line(int fd)
{
	int		len;
	char	*s;
	char	*buf;

	if (!fd)
		return (NULL);
	read(fd, buf, BUFFER_SIZE);
	len = ft_countc(buf);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s = ft_strncpy(s, buf, len);
	return (s);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*str;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	return (0);
}