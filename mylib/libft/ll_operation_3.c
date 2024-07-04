/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_operation_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:30:37 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/16 12:37:05 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	shifts the linkedlist up
*/
int	shift_first(t_node **list)
{
	t_node	*first;
	t_node	*last;

	if (!(list))
		return (0);
	if (!(*list))
		return (0);
	if (!((*list)->next))
		return (0);
	first = get_first_node(*list);
	last = get_last_node(*list);
	*list = first->next;
	first->next = NULL;
	last->next = first;
	return (1);
}

/*
	shifts the linked list down
*/
int	shift_last(t_node **list)
{
	t_node	*first;
	t_node	*last;
	t_node	*temp;

	if (!(list))
		return (0);
	if (!(*list))
		return (0);
	if (!((*list)->next))
		return (0);
	if (!((*list)->next->next))
	{
		shift_first(list);
		return (0);
	}
	first = get_first_node(*list);
	last = get_last_node(*list);
	temp = *list;
	while (temp->next->next)
		temp = temp->next;
	temp->next = NULL;
	last->next = first;
	*list = last;
	return (1);
}

int	pop(t_node **list)
{
	if (!list)
		return (0);
	(*list) = (*list)->next;
	return (1);
}
