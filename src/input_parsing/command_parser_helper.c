/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:13:10 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/29 12:06:36 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Create an AST node and initialize to nulls
*/
t_ast_node	*create_ast_node(t_token_type type)
{
	t_ast_node	*new;

	new = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->value = NULL;
	new->file_type = UNSET;
	new->type = type;
	return (new);
}

/*
	Counts the number of words (command + it's args)
*/
int	count_command_args(t_node *token)
{
	t_node	*temp;
	int		count;

	count = 0;
	temp = token;
	while (temp && temp->type == WORD)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

/*
	given a command type ast node it fills with the corresponding commands
	and frees the command because they're useless now
*/
void	fill_command_args(t_ast_node **command, t_node **tokens, int count)
{
	int		i;
	t_node	*temp;
	t_node	*prev;

	temp = *tokens;
	i = 0;
	while (i < count)
	{
		(*command)->value[i] = ft_strdup(temp->value);
		prev = temp;
		temp = temp->next;
		if (prev->value)
			free(prev->value);
		free(prev);
		i++;
	}
	(*command)->value[i] = NULL;
}

/*
	creates a file type node
	it's called from redirections
*/
t_ast_node	*create_file_node(t_node	*temp)
{
	t_ast_node	*file_node;

	file_node = create_ast_node(temp->type);
	file_node->value = (char **)malloc(sizeof(char *) * 2);
	file_node->value[1] = NULL;
	file_node->value[0] = ft_strdup(temp->value);
	free(temp->value);
	free(temp);
	return (file_node);
}
