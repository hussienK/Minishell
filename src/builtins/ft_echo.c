/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:16:56 by moassi            #+#    #+#             */
/*   Updated: 2024/07/03 22:46:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_no_line(char *s)
{
	int	i;

	if (s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **input)
{
	int		i;
	int		newl;
	int		first_print;

	newl = 1;
	i = 0;
	first_print = 1;
	while (input[++i] && is_no_line(input[i]))
		newl = 0;
	while (input[i])
	{
		if (first_print)
		{
			ft_putstr(input[i]);
			first_print = 0;
		}
		else
			ft_printf(" %s", input[i]);	
		i++;		
	}
	if (newl == 1)
		ft_putstr("\n");
	exit(0);
}
