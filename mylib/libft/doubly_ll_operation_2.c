/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_ll_operation_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:04:24 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/26 19:12:23 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	return first element in linkedlist
*/
t_node_d	*get_first_node_doubly(t_node_d *list)
{
	if (!list)
		return (NULL);
	return (list);
}

/*
	return second element in linkedlist
*/
t_node_d	*get_second_node_doubly(t_node_d *list)
{
	if (!list)
		return (NULL);
	if (!(list->next))
		return (NULL);
	return (list->next);
}

/*
	pop element from linkedlist
*/
int	remove_element_doubly(t_node_d **list)
{
	t_node_d	*temp;

	if (!list)
		return (0);
	temp = *list;
	(*list) = (*list)->next;
	(*list)->prev = NULL;
	free(temp);
	return (1);
}

/*
	reverse a linked list
*/
int	reverse_ll_doubly(t_node_d **list)
{
	t_node_d	*temp;
	t_node_d	*current;

	if (!(list) || !(*list))
		return (0);
	temp = NULL;
	current = *list;
	while (current != NULL)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	if (temp != NULL)
	{
		*list = temp->prev;
	}
	return (1);
}
