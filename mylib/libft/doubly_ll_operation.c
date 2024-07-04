/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_ll_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:36:32 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/23 17:15:27 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	creating nodes
*/
t_node_d	*create_node_doubly(int data)
{
	t_node_d	*temp;

	temp = (t_node_d *)malloc(sizeof(t_node_d));
	if (!temp)
		return (NULL);
	temp->next = NULL;
	temp->prev = NULL;
	temp->data = data;
	return (temp);
}

/*
	adding a node to beginning
*/
int	add_node_start_doubly(t_node_d **list, t_node_d *new)
{
	if (!new)
		return (0);
	if (!(list))
		return (0);
	new->next = (*list);
	if (*list)
		(*list)->prev = new;
	(*list) = new;
	return (1);
}

/*
	get last item
*/
t_node_d	*get_last_node_doubly(t_node_d *list)
{
	t_node_d	*temp;

	if (!list)
		return (NULL);
	temp = list;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

/*
	add an item to end of linked list
*/
int	add_to_back_doubly(t_node_d **list, t_node_d *new)
{
	t_node_d	*temp;

	if (!new || !list)
		return (0);
	if (!(*list))
	{
		(*list) = new;
		return (0);
	}
	temp = get_last_node_doubly(*list);
	temp->next = new;
	new->prev = temp;
	return (1);
}

/*
	get the length of a linked list
*/
int	list_length_doubly(t_node_d *list)
{
	size_t		i;
	t_node_d	*temp;

	temp = list;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
