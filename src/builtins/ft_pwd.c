/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:37:32 by moassi            #+#    #+#             */
/*   Updated: 2024/07/07 21:31:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_old(t_env *myenv)
{
	int		i;
	char	*p;

	i = -1;
	while (myenv->env[++i])
	{
		if (!ft_strncmp("PWD=", myenv->env[i], 4))
		{
			p =  myenv->env[i] + 4;
			ft_printf("%s\n", p);
			break;
		}
	}
}

int	ft_pwd(t_env *env)
{
	char	*dir;
	char	buf[4096];

	dir = getcwd(buf, sizeof(buf));
	if (!dir || dir[0] == '\0')
	{
		get_old(env);
	}
	else
		ft_printf("%s\n", dir);
	exit(0);
	return (1);
}
