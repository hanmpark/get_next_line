/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:35:29 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/03 19:53:44 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_is_nl(char *str)
{
	int		times;

	times = 0;
	if (!str)
		return (times);
	while (*str)
	{
		if (*str == '\n')
			times++;
		str++;
	}
	return (times);
}

int	ft_end_nl(char *str)
{
	while (*str)
		str++;
	if (*(str - 1) == '\n')
		return (1);
	return (0);
}

char	*ft_getline(int fd, char *stash, char *line)
{
	char	*buf;
	ssize_t	check;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_is_nl(stash))
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == -1)
		{
			free(buf);
			free(line);
			free(stash);
			return (NULL);
		}
		buf[check] = 0;
		stash = ft_bufferjoin(stash, buf);
		if (check == 0)
			break ;
	}
	free(buf);
	line = ft_bufferjoin(line, stash);
	free(stash);
	return (line);
}

char	*ft_checkline(char *line)
{
	char	*str;
	size_t	len;

	str = NULL;
	len = ft_strlen(line);
	if (ft_is_nl(line) == 1 && !ft_end_nl(line))
		str = ft_linetrim(line);
	else if (ft_is_nl(line) > 1)
		str = ft_linetrim(line);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	line = ft_getline(fd, stash, line);
	if (!line)
	{
		stash = NULL;
		return (NULL);
	}
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	stash = ft_checkline(line);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	int		line;
	int		linenbr;
	char	*str;

	if (argc != 2)
		return (printf("Too many arguments !\n"));
	else if (!atoi(argv[1]))
		return (printf("That's not a number !\n"));
	fd = open("text.txt", O_RDONLY);
	linenbr = 1;
	line = atoi(argv[1]);
	while (line--)
	{
		str = get_next_line(fd);
		printf("%d. line printed = %s", linenbr++, str);
		free(str);
		str = NULL;
	}
	//system("leaks a.out");
	return (0);
}
*/