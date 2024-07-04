/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organiser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:10:31 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/28 12:39:22 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	simple function to reset the organiser after processes
*/
void	set_to_zero(t_execution_organiser *org)
{
	org->current_pipe = 0;
	org->input_fd = 0;
	org->output_fd = 0;
	org->input_file_count = 0;
	org->output_file_count = 0;
	org->pipes_count = 0;
	org->has_in_file = 0;
	org->has_out_file = 0;
	org->is_redir_pipe = 0;
	org->heredoc = 0;
	org->child_count = 0;
	org->heredoc_second = 0;
}

/*
	counts the pipes, redirections to help manage executions
*/
void	init_counts(t_ast_node *head, t_execution_organiser *org)
{
	if (!head)
		return ;
	if (head->type == PIPE)
		org->pipes_count += 1;
	else if (head->type == REDIRECTION_APPEND
		|| head->type == REDIRECTION_OUT)
		org->output_file_count += 1;
	else if (head->type == REDIRECTION_IN
		|| head->type == REDIRECTION_HEREDOC)
		org->input_file_count += 1;
	if (head->left)
		init_counts(head->left, org);
	if (head->right)
		init_counts(head->right, org);
}

/*
	either resets the organisation variables
	or adds one to the curret pipe count
*/
void	init_organiser(t_execution_organiser *org, int reset_all)
{
	org->current_pipe = org->pipes_count;
	if (reset_all)
		set_to_zero(org);
	else if (org->pipes_count)
		org->current_pipe += 1;
	org->heredoc_second = 1;
}

/*
	sets the file type for everything to help with executions
	-the write to and read from file are set as their types
	-the operators are set as done since they have been executed
	-everything else is a command to be executed
*/
void	init_file_types(t_ast_node	*head)
{
	if (head->type != WORD)
	{
		head->file_type = DONE;
		if (head->type == REDIRECTION_OUT && head->right)
			head->right->file_type = OUT;
		else if (head->type == REDIRECTION_APPEND && head->right)
			head->right->file_type = OUT_APPEND;
		else if (head->type == REDIRECTION_IN && head->right)
			head->right->file_type = IN;
		else if (head->type == REDIRECTION_HEREDOC && head->right)
			head->right->file_type = IN_APPEND;
		else if (head->type == PIPE)
		{
			if (head->left)
				head->left->file_type = EXECUTABLE;
			if (head->right)
				head->right->file_type = EXECUTABLE;
		}
	}
	if (head->file_type == UNSET)
		head->file_type = EXECUTABLE;
	if (head->left)
		init_file_types(head->left);
	if (head->right)
		init_file_types(head->right);
}
