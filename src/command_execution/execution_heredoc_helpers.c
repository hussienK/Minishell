/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:38:24 by marvin            #+#    #+#             */
/*   Updated: 2024/07/04 12:38:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_qoutes_str(char *str, int single_qoute_count,
			int double_qoute_count, int i)
{
	char	*res;
	int		j;

	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '"' && !(single_qoute_count % 2))
			double_qoute_count++;
		else if (str[i] == '\'' && !(double_qoute_count % 2))
			single_qoute_count++;
		if ((str[i] != '"' || single_qoute_count % 2)
			&& (str[i] != '\'' || double_qoute_count % 2))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

int	check_if_solo_dollar_heredoc(char *str, int *j, int out_f)
{
	if (!str[*j] || str[*j + 1] == ' '
		|| (str[*j + 1] >= '!' && str[*j + 1] <= '/')
		|| (str[*j + 1] >= ':' && str[*j + 1] <= '@'
			&& str[*j + 1] != '?')
		|| (str[*j + 1] >= '[' && str[*j + 1] <= '`')
		|| (str[*j + 1] >= '{' && str[*j + 1] <= '~'))
	{
		ft_putstr_fd("$", out_f);
		(*j)++;
		return (1);
	}
	return (0);
}

void	expand_var(char *tofind, t_env *myenv, int out_f)
{
	int		i;
	char	*temp;

	i = 0;
	while (myenv->env[i])
	{
		if (!ft_strncmp(myenv->env[i], tofind, ft_strlen(tofind)))
		{
			temp = ft_strdup(myenv->env[i] + ft_strlen(tofind));
			if (temp[ft_strlen(temp) - 1] == '\n')
				temp[ft_strlen(temp) - 1] = '\0';
			if (!temp || temp[0] == '\0')
				return ;
			else
			{
				ft_putstr_fd(temp, out_f);
				free(temp);
				return ;
			}
			break ;
		}
		i++;
	}
}

void	get_var_heredoc(char *str, t_env *myenv, int *j, int out_f)
{
	int		i;
	char	*to_find;
	char	*tmp;


	(void)myenv;
	(void)out_f;
	(*j)++;
	i = 0;
	if ((str[*j] == '?'))
		i = 1;
	else
	{
		while (str[*j + i] && str[*j + i] != '$'
			&& str[*j + i] != '\'' && str[*j + i] != '"'
			&& str[*j + i] != ' ')
			i++;
	}
	to_find = ft_substr(str, *j, i);
	tmp = to_find;
	to_find = ft_strjoin(to_find, "=");
	free(tmp);
	(*j) += i;
	expand_var(to_find, myenv, out_f);
	free(to_find);
}

int	get_var_start_heredoc(char *str, int *j, int out_f)
{
	while (str[*j])
	{
		if (str[*j] == '$')
		{
			return (!check_if_solo_dollar_heredoc(str,
					j, out_f));
		}
		ft_putchar_fd(str[*j], out_f);
		(*j) += 1;
	}
	return (0);
}
