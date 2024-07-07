/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_printenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:55:25 by moassi            #+#    #+#             */
/*   Updated: 2024/07/05 10:56:41 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_ll(t_env_node **lst)
{
	if ((*lst)->next)
		free_ll(&((*lst)->next));
	free((*lst)->str);
	free(*lst);
}

static void	add_to_ll(t_env *myenv, t_env_node **env)
{
	t_env_node	*new;
	t_env_node	*cur;
	int			i;

	i = 0;
	while (myenv->env[i])
	{
		new = (t_env_node *)malloc(sizeof(t_env_node));
		new->next = NULL;
		new->str = ft_strdup(myenv->env[i]);
		if (!*env)
			*env = new;
		else
		{
			cur = *env;
			while (cur->next)
				cur = cur->next;
			cur->next = new;
		}
		i++;
	}
}

t_env_node	*sort_list(t_env_node *lst, int (*cmp)(char *, char *))
{
	int			swapped;
	t_env_node	*ptr;
	char		*temp;

	if (!lst || !lst->next)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = lst;
		while (ptr->next != NULL)
		{
			if ((*cmp)(ptr->str, ptr->next->str) > 0)
			{
				temp = ptr->str;
				ptr->str = ptr->next->str;
				ptr->next->str = temp;
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
	return (lst);
}

static void	get_var_and_val(char *str, char	**var, char	**val)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	*var = ft_substr(str, 0, i + 1);
	*val = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
}

void	sort_print_env(t_env *myenv)
{
	t_env_node	*env;
	t_env_node	*cur;
	char		*var;
	char		*val;

	env = NULL;
	add_to_ll(myenv, &env);
	env = sort_list(env, ft_strcmp);
	cur = env;
	while (cur)
	{
		get_var_and_val(cur->str, &var, &val);
		ft_printf("declare -x %s", var);
		if (strchr(cur->str, '='))
			ft_printf("\"%s\"", val);
		ft_printf("\n");
		free(var);
		free(val);
		cur = cur->next;
	}
	free_ll(&env);
}
