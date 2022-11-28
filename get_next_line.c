/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:49 by hanmpark          #+#    #+#             */
/*   Updated: 2022/11/28 12:10:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		i;
	char	*s;
	char	*buf;

	if (!fd)
		return (NULL);
	read(fd, buf, );
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*str;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	return (0);
}