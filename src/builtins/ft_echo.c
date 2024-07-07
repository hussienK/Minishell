/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:16:56 by moassi            #+#    #+#             */
/*   Updated: 2024/07/05 13:11:49 by hkanaan          ###   ########.fr       */
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

void	print_char_by_char(char **input, int with_space, int i)
{
	int	j;

	j = 0;
	if (with_space)
		ft_printf(" ");
	while (input[i][j])
	{
		if (input[i][j] == '\\')
		{
			if (input[i][j + 1] == '\\')
			{
				ft_printf("%c", '\\');
				j++;
			}
		}
		else
		{
			ft_printf("%c", input[i][j]);
		}
		j++;
	}
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
			print_char_by_char(input, 0, i);
			first_print = 0;
		}
		else
			print_char_by_char(input, 1, i);
		i++;
	}
	if (newl == 1)
		ft_putstr("\n");
	exit(0);
}
