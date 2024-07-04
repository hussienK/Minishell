/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:05:31 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/02 20:16:31 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

/*
	-if given a special token it returns the size and skips i
	based on it's size
*/
int	count_special_char(char *s, int *i)
{
	if (!ft_strncmp(&s[*i], "<<", 2) || !ft_strncmp(&s[*i], ">>", 2))
	{
		(*i) += 2;
		return (2);
	}
	if (!ft_strncmp(&s[*i], "<", 1) || !ft_strncmp(&s[*i], ">", 1)
		|| !ft_strncmp(&s[*i], "|", 1))
	{
		(*i) += 1;
		return (1);
	}
	return (-1);
}

int	is_stopper(char *s, int i)
{
	return (!s[i] || strncmp(&s[i], "<<", 2) == 0
		|| strncmp(&s[i], ">>", 2) == 0 || strncmp(&s[i], "<", 1) == 0
		|| strncmp(&s[i], ">", 1) == 0 || strncmp(&s[i], "|", 1) == 0
		|| s[i] == ' ' || s[i] == '\t');
}

int	deal_with_input(char *s, int *i, int *single_q, int *double_q)
{
	int	count;

	count = 0;
	while (s[*i])
	{
		if (s[*i] == '\'' && *double_q % 2 == 0)
		{
			*single_q ^= 1;
		}
		else if (s[*i] == '\"' && *single_q % 2 == 0)
		{
			*double_q ^= 1;
		}
		if (is_stopper(s, *i) && (*single_q % 2 == 0) && (*double_q % 2 == 0))
			return (count);
		(*i)++;
		count++;
	}
	return (count);
}

/*
	-used for counting anything that isn't a special or between qoutes
	-keeps counting and skipping chars until it reaches a special char
	or space or quotes
*/
int	count_command_char(char *s, int *i)
{
	int	count;
	int	temp;
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	count = 0;
	while (1)
	{
		if (!s[*i] || strncmp(&s[*i], "<<", 2) == 0
			|| strncmp(&s[*i], ">>", 2) == 0 || strncmp(&s[*i], "<", 1) == 0
			|| strncmp(&s[*i], ">", 1) == 0 || strncmp(&s[*i], "|", 1) == 0
			|| s[*i] == ' ' || s[*i] == '\t')
			return (count);
		temp = deal_with_input(s, i, &single_q, &double_q);
		count += temp;
	}
	return (count);
}

/*
	-called from outside to be able to count the next token
*/
int	count_tokens(char *input, int *i)
{
	int	count;

	count = -1;
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i) += 1;
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>'
		||!strncmp(&input[*i], "<<", 2) || !strncmp(&input[*i], ">>", 2))
		count = count_special_char(input, i);
	else if (input[*i])
		count = count_command_char(input, i);
	return (count);
}
