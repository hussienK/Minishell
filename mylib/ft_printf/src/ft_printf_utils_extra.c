/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:03:27 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/18 12:02:42 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ugetnbr_len(unsigned int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	else
	{
		while (n > 0)
		{
			l++;
			n /= 10;
		}
	}
	return (l);
}

void	ft_writeunbr(unsigned int n)
{
	if (n >= 10)
		ft_writeunbr(n / 10);
	ft_putchar((char)(n % 10 + 48));
}

int	ft_putunsigned_nb(unsigned int n)
{
	ft_writeunbr(n);
	return (ft_ugetnbr_len(n));
}

int	ft_putpercent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_sstrlen_p(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
