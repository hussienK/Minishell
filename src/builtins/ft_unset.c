/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:19:06 by moassi            #+#    #+#             */
/*   Updated: 2024/07/08 11:09:37 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_env *myenv, int remove_index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (myenv->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (myenv->env[i])
	{
		if (i != remove_index)
		{
			new_env[j] = ft_strdup(myenv->env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_mtrxc(myenv->env);
	myenv->env = new_env;
}

static int	check_valid(char *arg, int *invalid, int *exit_code)
{
	if (ft_strchr(arg, '!') && arg[1] && *invalid == 0)
	{
		ft_printf("unset: %s: event not found\n", arg);
		(*invalid)++;
		return (0);
	}
	else if (ft_strchr(arg, '(') || ft_strchr(arg, ')'))
	{
		ft_printf("unset: %s: syntax error near unexpected token\n", arg);
		(*invalid)++;
		*exit_code = 2;
		return (0);
	}
	return (1);
}

static void	check_and_delete_var(t_env *myenv, char *arg, int *invalid, int *ex)
{
	char	*trgt;
	int		i;

	if (!check_valid(arg, invalid, ex))
		return ;
	trgt = ft_strjoin(arg, "=");
	i = 0;
	while (myenv->env[i])
	{
		if (!strncmp(myenv->env[i], trgt, ft_strlen(trgt)))
		{
			update_env(myenv, i);
			break ;
		}
		i++;
	}
	free(trgt);
}

int	ft_unset(char **input, t_env *myenv)
{
	int		i;
	int		invalid;
	int		exit_code;

	exit_code = 0;
	if (!input[1])
		return (exit_code);
	invalid = 0;
	i = 1;
	while (input[i])
	{
		check_and_delete_var(myenv, input[i], &invalid, &exit_code);
		i++;
	}
	return (exit_code);
}
