/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 08:21:21 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/18 12:02:58 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = ft_sstrlen_p(s);
	write(1, s, i);
	return (i);
}

int	ft_getnbr_len(int n)
{
	int				l;
	unsigned int	num;

	l = 0;
	if (n < 0)
	{
		num = (unsigned int)(n * -1);
		l++;
	}
	else if (n == 0)
		return (1);
	else
		num = (unsigned int)n;
	while (num > 0)
	{
		l++;
		num /= 10;
	}
	return (l);
}

void	ft_writenbr(int n)
{
	unsigned int	num;

	if (n < 0)
	{
		ft_putchar('-');
		num = (unsigned int)(n * -1);
	}
	else
		num = (unsigned int)n;
	if (num >= 10)
		ft_writenbr(num / 10);
	ft_putchar((char)(num % 10 + 48));
}

int	ft_putnbr(int n)
{
	ft_writenbr(n);
	return (ft_getnbr_len(n));
}
