/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/11/30 19:14:17 by hanmpark         ###   ########.fr       */
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
	char		*buf;
	char		*line;
	static char	*stash;
	int			check;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	*line = 0;
	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		*stash = 0;
	}
	while (!check_n(stash))
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check < BUFFER_SIZE)
			buf[check] = 0;
		stash = ft_strjoin(stash, buf);
		if (check <= 0)
			break ;
	}
	line = ft_strjoin(line, stash);
	free(stash);
	free(buf);
	stash = ft_substr_n(line);
	printf("stash is now = |%s|\n", stash);
	return (line);
}

/*
#include <fcntl.h>
int	main(void)
{
	int		fd;
	int		line = 1;

	fd = open("text.txt", O_RDONLY);
	while (line--)
		printf("line printed = |%s|\n", get_next_line(fd));
	return (0);
}
*/