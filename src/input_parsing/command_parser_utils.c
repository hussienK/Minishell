/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:00:39 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/25 12:00:48 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char *s)
{
	return (!ft_strcmp(s, "|") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, "<") || !ft_strcmp(s, ">>"));
}

int	is_redir(t_token_type type)
{
	return (type == REDIRECTION_APPEND || type == REDIRECTION_HEREDOC
		|| type == REDIRECTION_IN || type == REDIRECTION_OUT);
}
