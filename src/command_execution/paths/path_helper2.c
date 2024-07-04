/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:46:10 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/03 22:57:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	displays path related errors
*/
int	display_file_path_errors(int failed, char *file)
{
	if (failed == 1)
	{
		ft_putstr_fd("Error in: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_signal_num = 1;
		return (127);
	}
	else if (failed)
	{
		ft_putstr_fd("Error in: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_signal_num = 1;
		return (127);
	}
	return (failed);
}
