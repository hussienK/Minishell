/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:19:06 by moassi            #+#    #+#             */
/*   Updated: 2024/07/02 20:01:19 by hkanaan          ###   ########.fr       */
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

static void	check_and_delete_var(t_env *myenv, char *arg, int *invalid)
{
	char	*trgt;
	int		i;

	if (strchr(arg, '='))
	{
		if (*invalid == 0)
		{
			ft_printf("unset: %s: invalid parameter name\n", arg);
			(*invalid)++;
		}
		return ;
	}
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

	if (!input[1])
	{
		return (0);
	}
	invalid = 0;
	i = 1;
	while (input[i])
	{
		check_and_delete_var(myenv, input[i], &invalid);
		i++;
	}
	return (0);
}
