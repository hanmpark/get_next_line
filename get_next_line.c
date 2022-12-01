/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/01 09:54:47 by hanmpark         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*stash;
	long long	check;

	if (fd < 1 || fd == 2)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	*line = 0;
	if (!stash || *stash == 0)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		*stash = 0;
	}
	while (!check_n(stash))
	{
		check = read(fd, buf, BUFFER_SIZE);
		//printf("+%lld ", check);
		if (check < BUFFER_SIZE)
			buf[check] = 0;
		stash = ft_buffjoin(stash, buf);
		//printf("%s\n", stash);
		if (check <= 0)
			break ;
	}
	line = ft_buffjoin(line, stash);
	free(stash);
	free(buf);
	if (!*line)
		return (NULL);
	stash = ft_substr_n(line);
	if (*stash == 0)
		free (stash);
	//printf("stash =|%s|\n", stash);
	return (line);
}

/*
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
*/