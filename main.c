/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:36:16 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/04 18:56:15 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
/*\*/
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
/**/
