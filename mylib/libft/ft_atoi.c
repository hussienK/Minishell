/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:42:27 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/10 15:53:48 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		ans;
	int		neg;

	i = 0;
	neg = 0;
	ans = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (neg == 1)
			ans = (ans * 10) - (nptr[i] - '0');
		else
			ans = (ans * 10) + (nptr[i] - '0');
		i++;
	}
	return (ans);
}
