/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:35:29 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/01 19:05:02 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	ft_is_nl(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_end_nl(char *str)
{
	while (*str)
		str++;
	if (*(str - 1) == '\n')
		return (1);
	return (0);
}

char	*ft_get_line(int fd, char *stash, char *line)
{
	char	*buf;
	int		check;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_is_nl(stash))
	{
		check = read(fd, buf, BUFFER_SIZE);
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

char	*ft_trim_line(char *line)
{
	char	*str;
	int		len;

	len = ft_strlen(line);
	if (ft_is_nl(line) && !ft_end_nl(line))
		str = ft_linetrim(line);
	else if (ft_end_nl(line) && len > 1 && line[len - 2] == '\n')
		str = ft_linetrim(line);
	else
		str = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	if (!stash || !*stash)
	{
		stash = ft_calloc(1, sizeof(char));
		if (!stash)
			return (NULL);
	}
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	line = ft_get_line(fd, stash, line);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	stash = ft_trim_line(line);
	printf("stash = %s\n", stash);
	return (line);
}

int	main(void)
{
	int		fd;
	int		line = 3;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	while (line--)
	{
		str = get_next_line(fd);
		printf("line printed = |%s|\n\n", str);
		free(str);
		str = NULL;
	}
	close(fd);
	system("leaks a.out");
	return (0);
}
