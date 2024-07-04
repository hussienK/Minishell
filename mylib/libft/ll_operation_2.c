/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_operation_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:04:24 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/23 17:14:51 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	return first element in linkedlist
*/
t_node	*get_first_node(t_node *list)
{
	if (!list)
		return (NULL);
	return (list);
}

/*
	return second element in linkedlist
*/
t_node	*get_second_node(t_node *list)
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
int	remove_element(t_node **list)
{
	t_node	*temp;

	if (!list)
		return (0);
	temp = *list;
	(*list) = (*list)->next;
	free(temp);
	return (1);
}

/*
	reverse a linked list
*/
int	reverse_ll(t_node **list)
{
	t_node	*prev;
	t_node	*current;
	t_node	*next;

	if (!(list) || !(*list))
		return (0);
	current = *list;
	prev = NULL;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*list = prev;
	return (1);
}
