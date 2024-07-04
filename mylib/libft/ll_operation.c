/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:36:32 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/26 12:24:09 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	creating nodes
*/
t_node	*create_node(t_token_type type, char *value)
{
	t_node	*temp;

	temp = (t_node *)malloc(sizeof(t_node));
	if (!temp)
		return (NULL);
	temp->next = NULL;
	temp->type = type;
	temp->value = value;
	return (temp);
}

/*
	adding a node to beginning
*/
int	add_node_start(t_node **list, t_node *new)
{
	if (!new)
		return (0);
	if (!(list))
		return (0);
	new->next = (*list);
	(*list) = new;
	return (1);
}

/*
	get last item
*/
t_node	*get_last_node(t_node *list)
{
	t_node	*temp;

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
int	add_to_back(t_node **list, t_node *new)
{
	t_node	*temp;

	if (!new || !list)
		return (0);
	new->next = NULL;
	if (!(*list))
	{
		(*list) = new;
		return (1);
	}
	temp = get_last_node(*list);
	temp->next = new;
	temp = *list;
	return (1);
}

/*
	get the length of a linked list
*/
int	list_length(t_node *list)
{
	size_t	i;
	t_node	*temp;

	temp = list;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
