/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/01 11:54:57 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

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

char	*ft_newline(char *stash, int fd)
{
	char		*str;
	char		*buf;
	long long	check;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	*str = 0;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	while (!check_n(stash))
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == 0)
			break ;
		else if (check < BUFFER_SIZE)
			buf[check] = 0;
		stash = ft_buffjoin(stash, buf);
	}
	str = ft_buffjoin(str, stash);
	free(buf);
	free(stash);
	return (str);
}
/*
** stash allocated '\0' byte.
** line -> str allocated '\0' byte.
** buf allocated BUFER_SIZE.
** stash -> free 1st stash to concatenate buf.
** line -> str -> allocated 
*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	if (!stash || !*stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		*stash = 0;
	}
	line = ft_newline(stash, fd);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	stash = ft_substr_n(line);
	printf("stash at the end = |%s|\n", stash);
	if (*stash == 0)
		free (stash);
	return (line);
}

/*\*/
#include <fcntl.h>
int	main(void)
{
	int		fd;
	int		line = 2;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	while (line--)
	{
		str = get_next_line(fd);
		printf("line printed = |%s|\n", str);
		free(str);
	}
	system("leaks a.out");
	return (0);
}
/**/