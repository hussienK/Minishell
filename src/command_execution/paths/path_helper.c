/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:02:31 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/03 23:00:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	searches in the enviroment variables
	whenever there is a '=' check before
	if name is PATH to get the path
*/
char	*get_env(char *start, char **env)
{
	int		i;
	int		j;
	char	*first_part;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		first_part = ft_substr(env[i], 0, j);
		if (env[i][j] == '=')
		{
			if (ft_strcmp(first_part, start) == 0)
			{
				free(first_part);
				return (env[i] + j + 1);
			}
		}
		free(first_part);
		i++;
	}
	return (NULL);
}

/*
	given an env variable to search in, searches this enviroment
	variable for the file, if it's found attempts to access using mode
*/
char	*get_file_path(char *file, t_env *my_env, char *env_var, int mode)
{
	char	*path;
	char	*temp;
	char	*ans;

	path = get_env(env_var, my_env->env);
	if (file[0] && file[0] == '.' && file[1] == '/')
		temp = ft_strdup(file + 1);
	else
	{
		temp = ft_strjoin(path, "/");
	}
	ans = ft_strjoin(path, temp);
	if (access(ans, mode) == 0)
	{
		if (temp)
			free(temp);
		return (ans);
	}
	if (temp)
		free(temp);
	if (ans)
		free(ans);
	return (NULL);
}

/*
	loops through enviroment for PATH
	made already in Pipex
*/
char	*get_path(char *cmd, t_env *my_env)
{
	int		i;
	char	*executable_path;
	char	**all_paths;
	char	*temp_path;

	i = -1;
	temp_path = get_env("PATH", my_env->env);
	if (!temp_path)
		return (NULL);
	all_paths = ft_split(temp_path, ':');
	while (all_paths[++i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		executable_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(executable_path, F_OK | X_OK) == 0)
			return (free_mtrxc(all_paths), executable_path);
		free(executable_path);
	}
	return (free_mtrxc(all_paths), ft_strdup(cmd));
}

/*
	searches for the command
*/
char	*get_command_path(char **cmd, t_env *my_env, int mode)
{
	char	*path;
	char	*temp;

	(void)my_env;
	path = NULL;
	if (is_builtin_command(cmd))
		path = ft_strdup(*cmd);
	else
	{
		temp = get_path(cmd[0], my_env);
		if (!temp)
			return (NULL);
		path = ft_strdup(temp);
		if (access(path, mode) == 0)
		{
			if (temp)
				free(temp);
			return (path);
		}
		else
			free(temp);
	}
	if (path)
		free(path);
	return (NULL);
}

/*
	some extra checks that can help determine exact error type
*/
void	do_file_path_checks(char *path, char *file, int *failed)
{
	struct stat	s;

	if (file && !ft_strcmp(file, ".."))
		*failed = 2;
	else if (file && !ft_strcmp(file, "."))
	{
		*failed = 1;
		errno = 2;
	}
	else if (!stat(path, &s) && s.st_mode & __S_IFDIR)
	{
		*failed = 2;
		errno = 13;
	}
}
