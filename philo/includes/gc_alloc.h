/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:23:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:16:51 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_ALLOC_H
# define GC_ALLOC_H

typedef struct s_list
{
	void	*content;
	struct s_list	*next;
}	t_list;

typedef struct s_garbage_collector
{
	t_list	*head;
}	t_gc;

void	free_and_exit(void);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);

void	*gc_alloc(size_t size);
void	gc_free(void *ptr);
void	gc_free_array(int n, void **ptr_array);
void	gc_free_all(void);

#endif
