/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 22:24:31 by moassi            #+#    #+#             */
/*   Updated: 2024/07/05 12:14:01 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	append a character node to the end of the ll representing the 
	string we are building.
*/
void	resolve_quotes(t_ll_node **lst, char *str, int *j, t_env *myenv)
{
	(*j)++;
	while (str[*j] && str[*j] != '"')
	{
		if (str[*j] == '$')
			search_and_add_var(lst, str, j, myenv);
		else
		{
			add_to_str(str[*j], lst);
			(*j)++;
		}
	}
	(*j)++;
}

void	resolve_literals(t_ll_node **lst, char *str, int *j, t_env *myenv)
{
	(void)myenv;
	(*j)++;
	while (str[*j] && str[*j] != '\'')
	{
		add_to_str(str[*j], lst);
		(*j)++;
	}
	(*j)++;
}

/*
	substitute the old string with the new cleaned version
*/
void	replace_cleaned_str(t_ll_node **lst, t_ast_node *head, int i)
{
	int			len;
	t_ll_node	*cur;
	char		*str;

	len = 0;
	cur = *lst;
	while (cur)
	{
		cur = cur->next;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return ;
	str[len] = '\0';
	len = 0;
	cur = *lst;
	while (cur)
	{
		str[len] = cur->c;
		cur = cur->next;
		len++;
	}
	free(head->value[i]);
	head->value[i] = str;
}

/*
	cleaning quotations
*/
void	clean_quotations(t_ast_node *head, int i, t_env *my_env)
{
	t_ll_node	*start;
	int			j;

	start = NULL;
	j = 0;
	if (!ft_strchr(head->value[i], '"') && !ft_strchr(head->value[i], '\'')
		&& !ft_strchr(head->value[i], '$'))
		return ;
	while (head->value[i][j])
	{
		if (head->value[i][j] == '"')
			resolve_quotes(&start, head->value[i], &j, my_env);
		else if (head->value[i][j] == '\'')
			resolve_literals(&start, head->value[i], &j, my_env);
		else if (head->value[i][j] == '$' && ((head->value[i][j + 1] == '"')
				|| (head->value[i][j + 1] == '\'')))
			j++;
		else if (head->value[i][j] == '$')
			search_and_add_var(&start, head->value[i], &j, my_env);
		else
			add_to_str(head->value[i][j++], &start);
	}
	(replace_cleaned_str(&start, head, i), free_char_ll(&start));
}

/*
	Traversing the tree recursively to clean quotations
*/
void	traverse_and_clean_tree(t_ast_node *head, t_env *my_env)
{
	int	i;

	if (head->left)
		traverse_and_clean_tree(head->left, my_env);
	if (head->right)
		traverse_and_clean_tree(head->right, my_env);
	if (head->file_type != DONE && head->file_type != IN_APPEND)
	{
		i = 0;
		while (head->value[i])
		{
			clean_quotations(head, i, my_env);
			i++;
		}
	}
}
