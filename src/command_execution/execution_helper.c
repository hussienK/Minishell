/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:32:55 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/03 12:58:46 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	helper function to close pipes for saving space
*/
void	close_pipes_helper(int fd, int fd_2)
{
	if (fd != -1)
		close(fd);
	if (fd_2 != -1)
		close(fd_2);
}

/*
	update the children fd according to what fd says
	-if there is an in file, the current std input is redirected to it
	-if there is an out file, the current std output is redirected to it
	-if part of a pipe then changes input and output accordingly
*/
void	change_fds_child(t_execution_organiser *org, int *fd, int *new_fd)
{
	if (org->is_redir_pipe && org->has_in_file)
	{
		dup2(org->input_fd, 0);
		close_pipes_helper(org->input_fd, -1);
	}
	if (org->is_redir_pipe && org->has_out_file)
	{
		dup2(org->output_fd, 1);
		close_pipes_helper(org->output_fd, -1);
	}
	if (org->current_pipe && org->current_pipe <= org->pipes_count
		&& (!org->has_in_file || !org->is_redir_pipe))
		dup2(fd[0], 0);
	if (org->current_pipe > 1 && (!org->has_out_file || !org->is_redir_pipe))
		dup2(new_fd[1], 1);
	else
		close_pipes_helper(new_fd[0], -1);
	close_pipes_helper(new_fd[0], new_fd[1]);
}

/*
	closes not needed pipes and updates states since we've finished executing
*/
void	change_fds_parent(t_execution_organiser *org, int *fd, int *new_fd)
{
	if (org->is_redir_pipe && org->has_in_file)
	{
		close_pipes_helper(org->input_fd, -1);
		org->has_in_file = 0;
	}
	if (org->is_redir_pipe && org->has_out_file)
	{
		close_pipes_helper(org->output_fd, -1);
		org->has_out_file = 0;
	}
	if (!org->has_in_file && !org->has_out_file)
		org->is_redir_pipe = 0;
	close_pipes_helper(new_fd[1], -1);
	close_pipes_helper(fd[0], -1);
	if (org->current_pipe > 1)
		fd[0] = new_fd[0];
	else
		close_pipes_helper(new_fd[0], -1);
}

/*
	just a helper to save lines.
*/
int	update_state_helper(t_execution_organiser *org,
	int *first, int *second, int error)
{
	if (!error)
	{
		if (*first)
			close_pipes_helper(*second, -1);
		*first = 1;
	}
	else
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		org->has_in_file = 0;
	}
	return (1);
}

/*
	opens files depending on type and updates the org accordingly
	om stands for open_mode, normitte
*/
int	open_redir_file(t_ast_node *head, t_execution_organiser *org,
	t_env *my_env, int failed)
{
	int	om;

	if (head->file_type == IN)
	{
		update_state_helper(org, &(org->has_in_file), &(org->input_fd), 0);
		org->input_fd = open(head->value[0], O_RDONLY);
		if (org->input_fd < 0)
			failed = update_state_helper(org, 0, 0, 1);
		return (failed);
	}
	else if (head->file_type == IN_APPEND)
	{
		update_state_helper(org, &(org->has_in_file), &(org->input_fd), 0);
		failed = here_doc(head->value[0], org, my_env);
		signal(SIGINT, ctrl_c_pressed);
		return (failed);
	}
	update_state_helper(org, &(org->has_out_file), &(org->output_fd), 0);
	om = O_TRUNC;
	if (head->file_type == OUT_APPEND)
		om = O_APPEND;
	org->output_fd = open(head->value[0], O_WRONLY | O_CREAT | om, 0666);
	if (org->output_fd < 0)
		failed = update_state_helper(org, 0, 0, 1);
	return (failed);
}
