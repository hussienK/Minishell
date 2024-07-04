/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_ptr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:39:54 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/12 14:50:03 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long	ft_strlen_p(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	rec_print(unsigned long n, const char *base)
{
	int	len;

	len = 0;
	if (n > (ft_strlen_p(base) - 1))
		len += rec_print(n / ft_strlen_p(base), base);
	len += ft_putchar(*(base + (n % ft_strlen_p(base))));
	return (len);
}

int	ft_put_ptr(unsigned long long format)
{
	unsigned long	n;
	const char		*base;
	int				len;

	n = (unsigned long)format;
	base = "0123456789abcdef";
	len = ft_putstr("0x");
	len += rec_print(n, base);
	return (len);
}
