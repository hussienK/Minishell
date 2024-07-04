/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:32:54 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/01 17:56:21 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	enters a new line
*/
void	ctrl_c_pressed(int signal_num)
{
	(void)signal_num;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	ft_printf("%s%s%s", ANSI_COLOR_GREEN, "● ", ANSI_COLOR_RESET);
	rl_on_new_line();
	rl_redisplay();
}

/*
	If a process is terminated by signal N, the exit status is usually 128 + N
*/
void	ctrl_c_pressed_child(int signal_number)
{
	if (signal_number == 2)
		g_signal_num = 130;
	else
	{
		ft_putstr_fd("exit", 1);
		g_signal_num = 131;
	}
	write(1, "\n", 1);
}

/*
	-redirects ctrl-c into it's functions
	-redirects ctrl-\ into ignore
*/
void	setup_signals(void)
{
	signal(SIGINT, ctrl_c_pressed);
	signal(SIGQUIT, SIG_IGN);
}
