/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:04:38 by moassi            #+#    #+#             */
/*   Updated: 2024/07/05 10:57:50 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env(char *var, char *value, t_env *myenv)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((myenv->env)[i])
	{
		i++;
	}
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((myenv->env)[i])
	{
		new_env[i] = ft_strdup((myenv->env)[i]);
		i++;
	}
	new_env[i] = ft_strjoin(var, value);
	new_env[i + 1] = NULL;
	free_mtrxc(myenv->env);
	(myenv->env) = new_env;
}

static void	update_env(char *var, char *value, t_env *myenv, int index)
{
	char	*tmp;

	tmp = (myenv->env)[index];
	(myenv->env)[index] = ft_strjoin(var, value);
	free(tmp);
}

int	add_or_update_to_env(char *var, char *value, t_env *myenv)
{
	int	i;
	int	l;

	i = 0;
	if (ft_strcmp(var, "?=") && !check_var_validity(var, value))
		return (1);
	l = ft_strlen(var);
	while ((myenv->env)[i])
	{
		if (!strncmp(var, (myenv->env)[i], ft_strlen(var))
			|| (!strncmp(var, (myenv->env)[i], l - 1) && !myenv->env[i][l - 1]))
		{
			update_env(var, value, myenv, i);
			free(value);
			free(var);
			return (0);
		}
		i++;
	}
	add_env(var, value, myenv);
	free(value);
	free(var);
	return (0);
}

static int	extract_var_and_val(char *str, t_env *myenv)
{
	int		i;
	int		val_len;
	char	*tmp;
	char	*var;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	var = ft_substr(str, 0, i + 1);
	value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	val_len = ft_strlen(value);
	if ((value[0] == '"' && value[val_len - 1] == '"')
		|| (value[0] == '\'' && value[val_len - 1] == '\''))
	{
		tmp = value;
		value = ft_substr(value, 1, ft_strlen(value) - 2);
		free(tmp);
	}
	return (add_or_update_to_env(var, value, myenv));
}

int	ft_export(char **input, t_env *myenv)
{
	int		i;
	int		exit_code;

	exit_code = 0;
	if (!input[1])
	{
		sort_print_env(myenv);
		return (0);
	}
	i = 1;
	while (input[i])
	{
		if (!strchr(input[i], '='))
		{
			if (!check_var_validity(input[i], ""))
				exit_code = 1;
			else if (!var_exists(input[i], myenv))
				add_env(ft_strdup(input[i]), ft_strdup(""), myenv);
			i++;
			continue ;
		}
		exit_code = extract_var_and_val(input[i], myenv);
		i++;
	}
	return (exit_code);
}
