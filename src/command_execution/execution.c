/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:25:34 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/03 12:40:43 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_num;

/*
	recursivelt loops over AST, if a command isn't built in
	and has a type of read in file, it's searched if it exists
	and permission and special checks are done
*/
int	check_for_read_permissions(t_ast_node *node, t_env *my_env)
{
	int		failed;
	char	*path;

	failed = 0;
	if (node->value && !is_builtin_command(node->value)
		&& node->file_type == IN)
	{
		path = get_file_path(node->value[0], my_env, "PWD", R_OK);
		if (path == NULL)
			failed = 0;
		else
		{
			do_file_path_checks(path, node->value[0], &failed);
			free(path);
		}
		failed = display_file_path_errors(failed, node->value[0]);
	}
	if (!failed && node->left)
		failed = check_for_read_permissions(node->left, my_env);
	if (!failed && node->right)
		failed = check_for_read_permissions(node->right, my_env);
	return (failed);
}

/*
	Starts the whole execution thing from the head, respecting priorities
*/
int	execute_node(t_ast_node *head, t_execution_organiser *org, t_env *my_env)
{
	int	fd[2];
	int	failed;

	fd[0] = -1;
	fd[1] = -1;
	if (head->file_type == DONE)
	{
		if (head->type == PIPE)
			failed = execute_pipe(head, org, my_env, fd);
		else if (is_redir(head->type))
			failed = execute_redir(head, org, my_env, fd);
	}
	if (head->file_type == EXECUTABLE)
		failed = execute_command(head->value, org, my_env, fd);
	failed = wait_for_children(failed, org);
	if (org->has_in_file)
		close(org->input_fd);
	if (org->has_out_file)
		close(org->output_fd);
	if (fd[0] != -1 || fd[1] != -1)
		close_pipes_helper(fd[0], fd[1]);
	g_signal_num = 0;
	return (failed);
}

/*
	starts a command execution
	for now it just prints path
*/
int	execute_command(char **cmd, t_execution_organiser *org,
		t_env *my_env, int *fd)
{
	int		failed;
	char	*path;

	failed = 0;
	path = get_command_path(cmd, my_env, X_OK);
	if (path)
	{
		if (cmd[0])
			free(cmd[0]);
		cmd[0] = path;
	}
	if (!is_builtin_command_fork(cmd))
		org->child_count += 1;
	if (!org->is_redir_pipe)
		failed = do_command(cmd, org, my_env, fd);
	else
		failed = do_command_redir(cmd, org, my_env, fd);
	if (org->current_pipe > 1)
		org->current_pipe -= 1;
	return (failed);
}

/*
	-initializes an organiser structure with data to manage executions
	-checks permissions for read in files
	-if no permission errors starts execution
*/

void	execute_commands(t_ast_node *head, t_env *my_env, int *result)
{
	t_execution_organiser	org;
	int						failed;

	init_organiser(&org, 1);
	init_counts(head, &org);
	init_organiser(&org, 0);
	init_file_types(head);
	traverse_and_clean_tree(head, my_env);
	failed = check_for_read_permissions(head, my_env);
	if (!failed)
		*result = execute_node(head, &org, my_env);
}

/*
	waits for all children to finish executing and updates
	org accordingly
*/
int	wait_for_children(int failed, t_execution_organiser *org)
{
	if (failed != 2 && failed != 126 && failed != 127
		&& org->child_count && org->heredoc_second)
	{
		while (org->child_count)
		{
			wait(&failed);
			org->child_count -= 1;
		}
		signal(SIGINT, ctrl_c_pressed);
		signal(SIGQUIT, SIG_IGN);
		if (!g_signal_num)
			return (WEXITSTATUS(failed));
		else
			return (g_signal_num);
	}
	return (failed);
}
