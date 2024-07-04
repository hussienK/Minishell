/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:50:13 by moassi            #+#    #+#             */
/*   Updated: 2024/07/04 10:17:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_old_pwd(t_env *myenv)
{
	char	*prev_pwd;
	int		i;

	i = -1;
	while (myenv->env[++i])
	{
		if (!ft_strncmp(myenv->env[i], "PWD=", 4))
		{
			prev_pwd = ft_strdup(myenv->env[i] + 4);
			if (prev_pwd[0] == '\0')
				prev_pwd = NULL;
			break;
		}
	}
	if (!prev_pwd)
		prev_pwd = ft_strdup("");
	add_or_update_to_env(ft_strdup("OLDPWD="), prev_pwd, myenv);
}

void	update_current_pwd(t_env *myenv)
{
	int		i;
	char	buf[4096];
	char	*dir;

	i = -1;
	update_old_pwd(myenv);
	while (myenv->env[++i])
	{
		if (!ft_strncmp(myenv->env[i], "PWD=", 4))
		{
			dir = ft_strdup(getcwd(buf, sizeof(buf)));
			add_or_update_to_env(ft_strdup("PWD="), dir, myenv);
			break;
		}
	}
}

static int	ft_cd_onearg(char *arg, t_env *myenv)
{
	char	*dir;
	char	*tmp;
	char	buf[4096];

	if (arg[0] == '/' || arg[0] == '.')
	{
		dir = ft_strdup(arg);
	}
	else
	{
		dir = getcwd(buf, sizeof(buf));
		tmp = ft_strjoin(dir, "/");
		dir = ft_strjoin(tmp, arg);
		free(tmp);
	}
	if (chdir(dir) == -1)
	{
		cd_error_display(dir);
		return (free(dir), 1);
	}
	if (dir)
		free(dir);
	update_current_pwd(myenv);
	return (0);
}

static int	ft_noarg(char **env, t_env *myenv)
{
	int		i;
	char	*dir;

	i = 0;
	dir = NULL;
	while (env[i])
	{
		if (!ft_strncmp("HOME=", env[i], 5))
		{
			dir = ft_substr(env[i], 5, ft_strlen(env[i]));
			break ;
		}
		i++;
	}
	if (chdir(dir) == -1)
	{
		cd_error_display(dir);
		free(dir);
		return (1);
	}
	if (dir)
		free(dir);
	update_current_pwd(myenv);
	return (0);
}

int	ft_cd(char **input, t_env *my_env)
{
	if (!input[1])
		return(ft_noarg(my_env->env, my_env));		
	else if (input[1] && !input[2])
	{	
		if (!ft_strcmp(input[1], "-"))
			return (cd_back(my_env));
		return(ft_cd_onearg(input[1], my_env));
	}
	return (1);
}
