/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:10:54 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/01 18:23:23 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	adds a node with the current data to linked list
*/
void	fill_token_data(char *input, t_node **ll, int prev_index, int i)
{
	char		*value;
	int			j;

	j = 0;
	value = (char *)malloc(sizeof(char) * ((i - prev_index) + 1));
	value[(i - prev_index)] = '\0';
	while (prev_index < i)
		value[j++] = input[prev_index++];
	if (value)
	{
		value = ft_strtrim(value, " \t");
		if (!ft_strcmp(value, ">"))
			add_to_back(ll, create_node(REDIRECTION_OUT, value));
		else if (!ft_strcmp(value, "<"))
			add_to_back(ll, create_node(REDIRECTION_IN, value));
		else if (!ft_strcmp(value, ">>"))
			add_to_back(ll, create_node(REDIRECTION_APPEND, value));
		else if (!ft_strcmp(value, "<<"))
			add_to_back(ll, create_node(REDIRECTION_HEREDOC, value));
		else if (!ft_strcmp(value, "|"))
			add_to_back(ll, create_node(PIPE, value));
		else
			add_to_back(ll, create_node(WORD, value));
	}
}

/*
	-loops over the given input and creates a token,
	tokens are (single qoute, double qoute, special char
	commands)
*/
t_node	*tokenize_input_mem(char *input)
{
	int			i;
	int			count;
	int			prev_index;
	t_node		*ll;

	i = 0;
	ll = NULL;
	while (input[i])
	{
		prev_index = i;
		count = count_tokens(input, &i);
		if (count <= 0)
			continue ;
		fill_token_data(input, &ll, prev_index, i);
	}
	if (check_errors(ll) == 0 || check_qoutes(ll) == 0)
	{
		free_token_ll(&ll);
		return (NULL);
	}
	return (ll);
}
