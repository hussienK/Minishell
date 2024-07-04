/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:27:31 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/28 18:33:20 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	called from other functions to create a leaf with commands
	and their arguments
*/
t_ast_node	*parse_command(t_node **tokens)
{
	t_ast_node	*command;
	int			word_count;

	command = create_ast_node(WORD);
	word_count = count_command_args(*tokens);
	command->value = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!command->value)
		return (NULL);
	fill_command_args(&command, tokens, word_count);
	return (command);
}

/*
	to save lines for parse_redir
	creates a redirection node and creates a file node to it's right
*/
t_ast_node	*create_and_link_redirection(t_node **tokens, t_node *tmp)
{
	t_ast_node	*redirect_node;

	redirect_node = create_ast_node((*tokens)->type);
	(*tokens) = (*tokens)->next->next;
	redirect_node->left = parse_redir(tokens);
	redirect_node->right = create_file_node(tmp->next);
	free(tmp->value);
	free(tmp);
	return (redirect_node);
}

/*
	creates a redirections node
	-it's left is a recursive calls to itself
	(it frees it self, so actually the recursive call
	checks it's right aswell)
	-it's right is a call to create a file
	falls back to search for a command if no redir is found
*/
t_ast_node	*parse_redir(t_node	**tokens)
{
	t_node		*start;
	t_node		*ittr;
	t_ast_node	*redir;

	if (!(*tokens))
		return (NULL);
	start = *tokens;
	if (is_redir((*tokens)->type))
		return (create_and_link_redirection(tokens, start));
	while (*tokens && (*tokens)->next)
	{
		ittr = (*tokens)->next;
		if (is_redir((*tokens)->next->type))
		{
			redir = create_ast_node((*tokens)->next->type);
			(*tokens)->next = (ittr)->next->next;
			redir->left = parse_redir(&start);
			redir->right = create_file_node(ittr->next);
			return (free(ittr->value), free(ittr), redir);
		}
		*tokens = ittr;
	}
	return (parse_command(&start));
}

/*
	creates a pipe node
	-it's left is a call to search for redirections
	-it's right is a recursive call to search for more pipes
	it falls back on search for redirections if nothing is found
*/
t_ast_node	*parse_pipe(t_node	**tokens)
{
	t_node		*start;
	t_node		*ittr;
	t_ast_node	*pipe;

	start = *tokens;
	while ((*tokens) && (*tokens)->next)
	{
		ittr = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			pipe = create_ast_node(PIPE);
			(*tokens)->next = NULL;
			pipe->left = parse_redir(&start);
			pipe->right = parse_pipe(&(ittr->next));
			free(ittr->value);
			free(ittr);
			return (pipe);
		}
		(*tokens) = ittr;
	}
	return (parse_redir(&start));
}

/*
	Starts the whole AST generation process
*/
t_ast_node	*parse_input(t_node **tokens)
{
	if (!tokens || !(*tokens))
		return (NULL);
	return (parse_pipe(tokens));
}
