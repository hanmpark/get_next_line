/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/11/30 14:05:21 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

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

int	check_n(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_chars_after_n(char *str)
{
	int	count;

	count = 0;
	while (*str && *str != '\n')
		str++;
	while (*str)
	{
		if (*str == '\n')
			str++;
		else
		{
			str++;
			count++;
		}
	}
	return (count);
}

int	ft_chars_before_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
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
	while (str[i])
	{
		if (str[i] == '\n')
			i++;
		else
		{
			*dst = str[i++];
			dst++;
		}
	}
	*dst = 0;
	str[i - j] = 0;
	return (dst - j);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;
	char		*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!stash)
		return (NULL);
	*stash = 0;
	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	*line = 0;
	while (!check_n(stash))
	{
		read(fd, buf, BUFFER_SIZE);
		ft_strcpy(stash, buf);
		printf("buf = |%s|\n", buf);
		printf("stash = |%s|\n", stash);
		if (!*line)
			ft_strcpy(line, stash);
		else
			line = ft_strjoin(line, stash);
		printf("line = |%s|\n \n", line);
	}
	free(buf);
	stash = ft_substr_n(line);
	printf("stash is now = |%s|\n", stash);
	return (line);
}

/*\*/
#include <fcntl.h>
int	main(void)
{
	int		fd;

	fd = open("text.txt", O_RDONLY);
	printf("fd=%d\n", fd);
	printf("line printed = |%s|\n", get_next_line(fd));
	return (0);
}
/**/
