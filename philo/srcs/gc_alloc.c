/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:37:44 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:04:10 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "gc_alloc.h"

t_gc	*get_gc(void)
{
	static t_gc	gc = {NULL};

	return (&gc);
}

//implement mutex lock
void	*gc_alloc(size_t size)
{
	t_gc	*gc;
	void	*ptr;
	t_list	*node;

	gc = get_gc();
	if (!size)
		free_and_exit();
	ptr = malloc(size);
	if (!ptr)
		free_and_exit();
	node = ft_lstnew(ptr);
	if (!node)
		free_and_exit();
	memset(ptr, 0, size);
	ft_lstadd_front(&(gc->head), node);
	return (ptr);
}

void	gc_free(void *ptr)
{
	t_gc	*gc;
	t_list	*curr;
	t_list	*prev;

	if (!ptr)
		return ;
	gc = get_gc();
	curr = gc->head;
	prev = NULL;
	while (curr)
	{
		if (curr->content == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				gc->head = curr->next;
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_free_array(int n, void **ptr_array)
{
	while (n--)
		gc_free(ptr_array[n]);
	gc_free(ptr_array);
}

void	gc_free_all(void)
{
	t_gc	*gc;
	t_list	*curr;
	t_list	*temp;

	gc = get_gc();
	curr = gc->head;
	while (curr)
	{
		temp = curr->next;
		if (curr -> content)
			free(curr->content);
		free(curr);
		curr = temp;
	}
	gc->head = NULL;
}
