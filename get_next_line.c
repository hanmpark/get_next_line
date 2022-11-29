/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/11/29 19:23:07 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
** Steps to follow:
** 1. read the file and put to buf
** 2. s[len] len = -> \n
** 3. find a way to keep the chars after the '\n' and read at the start of this
**
** txt.txt
**	Hello World
**	How are you today
**
** if (BUFFER_SIZE == 13)
** buf = "Hello World\nH"
** len = 11
** buf = "\nH" -> maybe put that in the struct
** buf = "\nHow are you to"
*/

int	ft_countc(char *str)
{
	int	count;

	count = 0;
	while (str[count] && str[count] != '\n')
		count++;
	return (count);
}

int	ft_count_after(char *str)
{
	int	count;

	count = 0;
	while (*str && *str != '\n')
		str++;
	while (*str)
	{
		str++;
		count++;
	}
	return (count);
}

char	*ft_strncpy(char *s, char *buf, size_t len)
{
	int	i;

	i = 0;
	while (buf[i] && len--)
	{
		s[i] = buf[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*get_next_line(int fd)
{
	int			len;
	char		*s;
	static char	*buf;
	int			countafter;
	int			bcount; //for printf

	countafter = 0;
	if (buf)
	{
		countafter = ft_count_after(buf);
		free(buf);
	}
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	bcount = read(fd, buf, BUFFER_SIZE);
	printf("bytes read=%d\n", bcount);
	len = ft_countc(buf);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s = ft_strncpy(s, buf, len);
	return (s);
}

#include <fcntl.h>
int	main(void)
{
	int		fd;

	fd = open("text.txt", O_RDONLY);
	printf("fd=%d\n", fd);
	printf("%s\n", get_next_line(fd));
	return (0);
}