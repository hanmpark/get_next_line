/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:35:29 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/02 19:41:18 by hanmpark         ###   ########.fr       */
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

char	*ft_getline(int fd, char *stash, char *line)
{
	char	*buf;
	int		check;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_is_nl(stash))
	{
		check = read(fd, buf, BUFFER_SIZE);
		printf("check = %d\n", check);
		if (check <= 0)
			break ;
		buf[check] = 0;
		stash = ft_bufferjoin(stash, buf);
	}
	free(buf);
	if (check == -1)
	{
		free(stash);
		free(line);
		return (NULL);
	}
	line = ft_bufferjoin(line, stash);
	free(stash);
	return (line);
}

char	*ft_checkline(char *line)
{
	char	*str;
	int		len;

	if (!line)
	{
		line = NULL;
		return (NULL);
	}
	if (!*line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	str = NULL;
	len = ft_strlen(line);
	if (ft_is_nl(line) && !ft_end_nl(line))
		str = ft_linetrim(line);
	else if (ft_end_nl(line) && len > 1 && line[len - 2] == '\n')
		str = ft_linetrim(line);
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
	line = ft_getline(fd, stash, line);
	stash = ft_checkline(line);
	return (line);
}

int	main(void)
{
	int		fd;
	int		line = 1;
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
