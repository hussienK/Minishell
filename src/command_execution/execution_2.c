/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:05:01 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/03 22:51:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Called when compiling a pipe type
	it's recursive and calls itself, the base condition is finding a redirection
	or a command
*/
int	execute_pipe(t_ast_node *head, t_execution_organiser *org,
	t_env *my_env, int *fd)
{
	int	failed;

	failed = 0;
	if (head->file_type == EXECUTABLE)
	{
		org->is_redir_pipe = 0;
		failed = execute_command(head->value, org, my_env, fd);
	}
	if (is_redir(head->type))
		return (execute_redir(head, org, my_env, fd));
	if (head->left)
		failed = execute_pipe(head->left, org, my_env, fd);
	if (head->right)
	{
		failed = execute_pipe(head->right, org, my_env, fd);
	}
	return (failed);
}

/*
	-executes a redirectory node, checks the right node if it's accesable
	and opens it
	-executes left part  depending on it's type
*/
int	execute_redir(t_ast_node *head, t_execution_organiser *org,
	t_env *my_env, int *fd)
{
	int	failed;

	org->heredoc_second = 1;
	if (head->right)
	{
		failed = open_redir_file(head->right, org, my_env, 0);
		if ((failed || !head->left) && org->current_pipe > 1)
			org->current_pipe -= 1;
	}
	if (!failed && head->left && head->left->file_type == EXECUTABLE
		&& org->heredoc_second)
	{
		org->is_redir_pipe = 1;
		failed = execute_command(head->left->value, org, my_env, fd);
	}
	if (head->left && head->left->type == PIPE && org->heredoc_second)
		failed = execute_pipe(head->left, org, my_env, fd);
	if (!failed && head->left && is_redir(head->left->type))
		failed = execute_redir(head->left, org, my_env, fd);
	return (failed);
}

/*
	-executes a child process that's basic
	-if this isn't the first command it redirects input of prev
	into std input of this
	-if there is more commands after it redirects the output of it
	to the new pipe
	-after duplicating the file decryptors it needs it closes the newly created
	ontes
	-finally executes the commands
	-if there's more commands and after the input is prepared by duplicating 
*/
int	do_command(char **cmd, t_execution_organiser *org,
	t_env *my_env, int *fd)
{
	int		new_fd[2];
	pid_t	pid;
	int		code;

	code = do_builtin_cmd_parent(cmd, my_env);
	if (code != -42)
		return (code);
	pipe(new_fd);
	pid = fork();
	signal(SIGINT, ctrl_c_pressed_child);
	signal(SIGQUIT, ctrl_c_pressed_child);
	if (!pid)
	{
		if (strcmp(cmd[0], "") == 0)
			cmd[0] = NULL;
		do_command_helper(org, new_fd, fd);
		do_command_helper_2(cmd, my_env);
	}
	close_pipes_helper(new_fd[1], fd[0]);
	if (org->current_pipe > 1)
		fd[0] = new_fd[0];
	else
		close_pipes_helper(new_fd[0], -1);
	return (1);
}

/*
	- executes proper fd changes for both child and parent
	- calls the exectute in child
*/
int	do_command_redir(char **cmd, t_execution_organiser *org,
	t_env *my_env, int *fd)
{
	pid_t	pid;
	int		new_fd[2];

	pipe(new_fd);
	pid = fork();
	signal(SIGINT, ctrl_c_pressed_child);
	signal(SIGQUIT, ctrl_c_pressed_child);
	if (!pid)
	{
		if (strcmp(cmd[0], "") == 0)
			cmd[0] = NULL;
		change_fds_child(org, fd, new_fd);
		if (!do_builtin_cmd(cmd, my_env))
			execve(cmd[0], cmd, my_env->env);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		exit(127);
	}
	change_fds_parent(org, fd, new_fd);
	return (1);
}
