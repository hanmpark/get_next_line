/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:58:18 by hanmpark          #+#    #+#             */
/*   Updated: 2022/11/29 19:37:40 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->tmp = content;
	lst->next = 0;
	return (lst);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		if (lst->tmp)
		{
			del(lst->tmp);
			free(lst);
		}
		lst = NULL;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*theone;
	t_list	*next;

	if (lst && del)
	{
		theone = *lst;
		while (theone)
		{
			next = theone->next;
			ft_lstdelone(theone, del);
			theone = next;
		}
		*lst = NULL;
	}
}
