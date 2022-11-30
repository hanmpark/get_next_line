/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/11/30 10:35:00 by hanmpark         ###   ########.fr       */
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

int	check_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
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
		str++;
		count++;
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
		*dst = str[i++];
		dst++;
	}
	str[i - j] = 0;
	return (dst - j);
}
#include <string.h>
char	*get_next_line(int fd)
{
	char	*line;
	char	*stash;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	line = strdup("");
	while (!check_n(line))
	{
		read(fd, buf, BUFFER_SIZE);
		stash = malloc(BUFFER_SIZE * sizeof(char));
		if (!stash)
			return (NULL);
		ft_strcpy(stash, buf);
		if (!line)
			line = strdup(stash);
		line = ft_strjoin(line, stash);
		printf("stash = |%s|\n", line);
	}
	free(buf);
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