/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:05:13 by moassi            #+#    #+#             */
/*   Updated: 2024/07/02 14:06:39 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_error(char *var, char *value)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(value, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

int	check_var_validity(char *var, char *value)
{
	char	*set;
	int		i;

	set = "*/~-!@#&^()";
	i = 0;
	if (!(var[i] >= 'a' && var[i] <= 'z') && !(var[i] >= 'A' && var[i] <= 'Z'))
	{
		print_export_error(var, value);
		return (0);
	}
	while (var[i])
	{
		if (strchr(set, var[i]))
		{
			print_export_error(var, value);
			return (0);
		}
		i++;
	}
	return (1);
}
