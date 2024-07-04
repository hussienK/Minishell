/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:10:56 by moassi            #+#    #+#             */
/*   Updated: 2024/07/03 23:42:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_level(t_env *myenv)
{
	char	*prev_level;
	int		temp;

	int i = 0;
	while (myenv->env[i])
	{
		if (!ft_strncmp(myenv->env[i], "SHLVL=", 6))
		{
			prev_level = myenv->env[i] + 6;
			if (prev_level[0] == '\0')
				temp = 0;
			else
			{
				temp = ft_atoi(prev_level);
				temp += 1;
				prev_level = ft_itoa(temp);
				add_or_update_to_env(ft_strdup("SHLVL="),
					prev_level, myenv);
			}
			return ;
		}
		i++;
	}
}

t_env	*init_env(char **env)
{
	t_env	*myenv;
	int		i;

	i = 0;
	myenv = (t_env *)malloc(sizeof(t_env));
	if (!myenv)
		return (NULL);
	myenv->exit_code = 0;
	while (env[i])
		i++;
	myenv->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!myenv->env)
	{
		free(myenv);
		return (NULL);
	}
	i = 0;
	while (env[i])
	{
		(myenv->env)[i] = ft_strdup(env[i]);
		i++;
	}
	(myenv->env)[i] = NULL;
	update_env_level(myenv);
	return (myenv);
}

void	ft_free_env(t_env **myenv)
{
	int	i;

	i = 0;
	if (!myenv || !(*myenv))
		return ;
	while (((*myenv)->env)[i])
	{
		ft_printf("hello");
		free(((*myenv)->env)[i]);
		i++;
	}
	free((*myenv)->env);
	free(*myenv);
}
