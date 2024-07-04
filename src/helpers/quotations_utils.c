/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:17:11 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/01 18:02:57 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_str(char c, t_ll_node **lst)
{
	t_ll_node	*new;
	t_ll_node	*cur;

	new = (t_ll_node *)malloc(sizeof(t_ll_node));
	new->c = c;
	new->next = NULL;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	free_char_ll(t_ll_node **start)
{
	if (!*start)
		return ;
	if ((*start)->next)
		free_char_ll(&((*start)->next));
	free(*start);
}
