/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:13:32 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/02 11:26:28 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_and_display_exitcode(int exitcode, t_env *my_env)
{
	char	*temp;
	char	*temp2;

	temp = ft_itoa(exitcode);
	temp2 = ft_strdup("?=");
	add_or_update_to_env(temp2, temp, my_env);
	my_env->exit_code = exitcode;
	if (exitcode == 0)
		ft_printf("%s%s%s", ANSI_COLOR_GREEN, "● ", ANSI_COLOR_RESET);
	else
		ft_printf("%s%s%s", ANSI_COLOR_RED, "● ", ANSI_COLOR_RESET);
}
