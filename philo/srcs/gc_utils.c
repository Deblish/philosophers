/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:10:58 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/05 13:29:14 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "gc_alloc.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lstptr;

	lstptr = (malloc(sizeof(t_list)));
	if (!lstptr)
		return (NULL);
	lstptr->content = content;
	lstptr->next = NULL;
	return (lstptr);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	free_and_exit(void)
{
	gc_free_all();
	exit(EXIT_FAILURE);
}