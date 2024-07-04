/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:08:24 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/03 23:21:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **input, t_env *my_env)
{
	int	exit_code;

	if (!input || !(*input))
		exit(my_env->exit_code);
	if (!ft_strcmp(input[0], "exit"))
	{
		exit_code = my_env->exit_code;
		if (input[1] && input[2])
		{
			my_env->exit_code = 1;
			ft_putendl_fd("exit: too many arguments", 2);
			if (ft_str_numeric(input[1]))
				return (1);
		}
		else if (input[1] && !ft_str_numeric(input[1]))
			exit_code = 2;
		else if (input[1])
			exit_code = ft_atoi(input[1]);
		if (exit_code == 2)
			ft_putendl_fd("exit: numeric argument required", 2);
		ft_putendl_fd("exit", 1);
		free_ast_tree(my_env->tree);
		(free_mtrxc(my_env->env), free(my_env), exit(exit_code));
	}
	return (0);
}
