/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:06:51 by moassi            #+#    #+#             */
/*   Updated: 2024/07/07 20:57:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_builtin_cmd(char **input, t_env *myenv)
{
	if (!ft_strcmp("echo", input[0]))
	{
		ft_echo(input);
		return (1);
	}
	else if (!ft_strcmp("pwd", input[0]))
		return (ft_pwd(myenv));
	else if (!ft_strcmp("env", input[0]))
		return (ft_env(input, myenv));
	return (0);
}

int	do_builtin_cmd_parent(char **input, t_env *myenv)
{
	if (!ft_strcmp("exit", input[0]))
		return(ft_exit(input, myenv));
	else if (!ft_strcmp("export", input[0]))
		return (ft_export(input, myenv));
	else if (!ft_strcmp("unset", input[0]))
		return (ft_unset(input, myenv));
	else if (!ft_strcmp("cd", input[0]))
		return (ft_cd(input, myenv));
	return (-42);
}
