/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_ll_operation_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:30:37 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/16 19:15:41 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	shifts the linkedlist up
*/
int	shift_first_doubly(t_node_d **list)
{
	t_node_d	*first;
	t_node_d	*last;

	if (!(list))
		return (0);
	if (!(*list))
		return (0);
	if (!((*list)->next))
		return (0);
	first = get_first_node_doubly(*list);
	last = get_last_node_doubly(*list);
	*list = first->next;
	(*list)->prev = NULL;
	first->next = NULL;
	first->prev = last;
	last->next = first;
	return (1);
}

/*
	shifts the linked list down
*/
int	shift_last_doubly(t_node_d **list)
{
	t_node_d	*first;
	t_node_d	*last;
	t_node_d	*temp;

	if (!(list) || !(*list))
		return (0);
	if (!((*list)->next))
		return (0);
	if (!((*list)->next->next))
	{
		shift_first_doubly(list);
		return (0);
	}
	first = get_first_node_doubly(*list);
	last = get_last_node_doubly(*list);
	temp = *list;
	while (temp->next->next)
		temp = temp->next;
	temp->next = NULL;
	last->next = first;
	first->prev = last;
	last->prev = NULL;
	*list = last;
	return (1);
}

int	pop_doubly(t_node_d **list)
{
	if (!list || !(*list))
		return (0);
	(*list) = (*list)->next;
	if (*list)
		(*list)->prev = NULL;
	return (1);
}
