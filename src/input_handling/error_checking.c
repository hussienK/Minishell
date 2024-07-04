/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:08:02 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/02 19:07:48 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	checks if a given string has an unclosed qoute
*/
int	qoutes_closed(char *input)
{
	char	qoute_type;
	int		i;

	i = 0;
	qoute_type = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (input[i] == qoute_type)
				qoute_type = 0;
			else if (qoute_type == 0)
				qoute_type = input[i];
		}
		i++;
	}
	return (qoute_type != 0);
}

/*
	-searches for an error in input syntax
	- a binary operation with less than 2 inputs
*/
t_node	*get_errors(t_node *ll)
{
	t_node	*temp;

	temp = ll;
	while (temp)
	{
		if (!ft_strncmp(temp->value, "<<", 2))
		{
			if (!temp->next)
				return (temp);
		}
		else if (!ft_strncmp(temp->value, "|", 1)
			|| (!ft_strncmp(temp->value, "<", 1
					&& ft_strncmp(temp->value, "<<", 2)))
			|| !ft_strncmp(temp->value, ">", 1)
			|| !ft_strncmp(temp->value, ">>", 2))
		{
			if (!temp->next || ll == temp)
				return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

int	check_qoutes(t_node *ll)
{
	t_node	*temp;

	temp = ll;
	while (temp)
	{
		if (qoutes_closed(temp->value))
		{
			ft_putendl_fd("Syntax error: unclosed qoutes", 2);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

/*
	- checks for errors in syntax
	- if there is an error prints a message depending on type
*/
int	check_errors(t_node *ll)
{
	t_node	*temp;

	temp = get_errors(ll);
	if (temp != NULL)
	{
		if (!ft_strncmp(temp->value, "|", 1))
		{
			printf("Error: %s should have command", temp->value);
			printf(" before and after\n");
			return (0);
		}
		else if (!ft_strncmp(temp->value, "<<", 2))
		{
			printf("Error: %s should be followed ", temp->value);
			printf("by a valid delimeter\n");
			return (0);
		}
		else
		{
			printf("Error: %s should have command", temp->value);
			printf(" before and be followed by a valid filename\n");
			return (0);
		}
	}
	return (1);
}
