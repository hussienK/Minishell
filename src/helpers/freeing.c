/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:37:00 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/02 20:01:19 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	frees a linked list
*/
void	free_token_ll(t_node **ll)
{
	t_node		*prev;
	t_node		*temp;

	temp = *ll;
	while (temp)
	{
		prev = temp;
		temp = temp->next;
		if (prev->value)
			free(prev->value);
		free(prev);
	}
}

/*
	frees a 2d matrix made out of chars
*/
void	free_mtrxc(char **m)
{
	int	i;

	i = 0;
	if (!m || !(*m))
		return ;
	i = 0;
	while (m[i])
		free(m[i++]);
	free(m);
}

/*
	frees an AST tree
*/
void	free_ast_tree(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast_tree(node->left);
	if (node->right)
		free_ast_tree(node->right);
	if (node->value)
		free_mtrxc(node->value);
	free(node);
}
