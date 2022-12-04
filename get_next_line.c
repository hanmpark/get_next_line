/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:35:29 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/04 18:58:36 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	ft_freeall(char *buf, char *line, char *stash)
{
	free(buf);
	free(line);
	free(stash);
}

char	*ft_getline(int fd, char *stash, char *line)
{
	char	*buf;
	ssize_t	check;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	check = BUFFER_SIZE;
	while (check == BUFFER_SIZE && !ft_is_nl(stash))
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == -1)
		{
			ft_freeall(buf, line, stash);
			return (NULL);
		}
		buf[check] = 0;
		stash = ft_bufferjoin(stash, buf);
	}
	free(buf);
	line = ft_bufferjoin(line, stash);
	free(stash);
	return (line);
}

char	*ft_checktrim(char *line)
{
	char	*stash;
	int		i;

	stash = NULL;
	i = 0;
	if (ft_is_nl(line) == 1)
	{
		while (line[i + 1])
			i++;
		if (line[i] != '\n')
			stash = ft_linetrim(line);
	}
	if (ft_is_nl(line) > 1)
		stash = ft_linetrim(line);
	return (stash);
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
	stash = ft_checktrim(line);
	return (line);
}
