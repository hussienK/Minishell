/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:43:43 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/01 16:23:40 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	curr_occurs(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] == c)
		i++;
	return (i);
}

/*
	-given the args and the opened fd it keeps getting
	args and piping them to parent aslong as there isn't
	delimiter
*/
void	here_doc_put_in(char *delim, int out_f)
{
	char	*ret;

	while (1)
	{
		ret = readline("> ");
		if (!ret || !ft_strcmp(ret, delim))
		{
			free(ret);
			break ;
		}
		ft_putendl_fd(ret, out_f);
		free(ret);
	}
}

void	quit_heredoc_helper(int signal_number)
{
	(void)signal_number;
	write(1, "\n", 1);
	exit(0);
}

/*
	-given the args it calls a fork and creates a pip
	-the child takes input from user and the parent gets 
	that input
*/
int	here_doc(char *delim, t_execution_organiser *org, t_env *my_env)
{
	int		new_fd[2];
	pid_t	pid;
	int		failed;

	(void)my_env;
	if (pipe(new_fd) == -1)
		exit (0);
	pid = fork();
	if (pid == -1)
		exit (0);
	if (!pid)
	{
		signal(SIGINT, quit_heredoc_helper);
		close(new_fd[0]);
		here_doc_put_in(delim, new_fd[1]);
		exit(1);
	}
	waitpid(pid, &failed, 0);
	close(new_fd[1]);
	org->input_fd = new_fd[0];
	org->heredoc = (WEXITSTATUS(failed)) - 1;
	if (org->heredoc < 0)
		org->heredoc += 2;
	org->heredoc_second = failed;
	return (org->heredoc);
}
