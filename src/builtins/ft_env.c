/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:53:47 by moassi            #+#    #+#             */
/*   Updated: 2024/07/02 13:19:34 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **input, t_env *my_env)
{
	int		i;

	if (input[1])
	{
		ft_printf("env: '%s': No such file or directory\n", input[1]);
		exit(1);
		return (1);
	}
	i = 0;
	while (my_env->env[i])
	{
		ft_putendl_fd(my_env->env[i], 1);
		i++;
	}
	exit(0);
	return (0);
}
