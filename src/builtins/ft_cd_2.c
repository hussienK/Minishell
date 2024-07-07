/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:53:00 by marvin            #+#    #+#             */
/*   Updated: 2024/07/04 09:53:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_back(t_env *myenv)
{
	int		i;
	char	*dir;

	i = -1;
	dir = NULL;
	while (myenv->env[++i])
	{
		if (!ft_strncmp("OLDPWD=", myenv->env[i], 7))
		{
			dir = ft_substr(myenv->env[i], 7, ft_strlen(myenv->env[i]));
			break ;
		}
	}
	if (!dir || dir[0] == '\0')
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(myenv->env[i], 2);
		return (free(dir), 1);
	}
	free(dir), update_current_pwd(myenv, 0);
	return (0);
}

void	cd_error_display(char *dir)
{
	struct stat	s;

	if (access(dir, F_OK) == 0 && !(!stat(dir, &s)
			&& s.st_mode & __S_IFDIR))
	{
		ft_putstr_fd("cd: cd into file: ", 2);
		ft_putendl_fd(dir, 2);
		return ;
	}
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(dir, 2);
}
