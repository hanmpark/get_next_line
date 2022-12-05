/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 07:24:59 by hanmpark          #+#    #+#             */
/*   Updated: 2022/12/05 07:30:09 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
/*\*/
int	main(int argc, char **argv)
{
	int		text;
	int		text1;
	int		text2;
	int		line;
	int		linenbr;
	char	*str;

	if (argc != 2)
		return (printf("Too many arguments !\n"));
	else if (!atoi(argv[1]))
		return (printf("That's not a number !\n"));
	text = open("text.txt", O_RDONLY);
	text1 = open("text1.txt", O_RDONLY);
	text2 = open("text2.txt", O_RDONLY);
	linenbr = 1;
	line = atoi(argv[1]);
	while (line--)
	{
		str = get_next_line(text);
		printf("1st\n%d. line printed = %s\n", linenbr, str);
		free(str);
		str = get_next_line(text1);
		printf("2nd\n%d. line printed = %s\n", linenbr, str);
		free(str);
		str = get_next_line(text2);
		printf("3rd\n%d. line printed = %s\n", linenbr++, str);
		free(str);
	}
	close(text);
	close(text1);
	close(text2);
	//system("leaks a.out");
	return (0);
}
/**/
