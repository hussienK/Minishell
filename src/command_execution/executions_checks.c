/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:40:46 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/03 23:26:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	a helper to check if a command is builtin
*/
int	is_builtin_command(char **cmd)
{
	if (!cmd || !(*cmd))
		return (0);
	return (!ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "cd")
		|| !ft_strcmp(cmd[0], "pwd")
		|| !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "exit"));
}

/*
	to save lines for norminette
*/
void	do_command_helper(t_execution_organiser *org, int *new_fd,
			int *fd)
{
	if (org->current_pipe && org->current_pipe <= org->pipes_count)
		dup2(fd[0], 0);
	if (org->current_pipe > 1)
		dup2(new_fd[1], 1);
	else
		close_pipes_helper(fd[0], -1);
	close_pipes_helper(new_fd[0], new_fd[1]);
}

/*
	to save lines for norminette
*/
void	do_command_helper_2(char **cmd, t_env *my_env)
{		
	if (!do_builtin_cmd(cmd, my_env))
		execve(cmd[0], cmd, my_env->env);
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	if (!access(cmd[0], F_OK))
		exit(126);
	exit(127);
}

/*
	builtins that need forking
*/
int	is_builtin_command_fork(char **cmd)
{
	if (!cmd || !(*cmd))
		return (0);
	return (!ft_strcmp(cmd[0], "cd")
		|| !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "exit"));
}
