/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 08:45:30 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/12 16:16:30 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Takes the compiled arguments and prints the correct thing according to the flag
	returns the nb of printed chars
*/
int	handle_conversions(const char flag, va_list args)
{
	unsigned long long int	a;

	if (flag == 'c')
		return (ft_putchar(va_arg(args, unsigned int)));
	else if (flag == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (flag == 'd' || flag == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (flag == 'u')
		return (ft_putunsigned_nb(va_arg(args, unsigned int)));
	else if (flag == '%')
		return (ft_putpercent());
	else if (flag == 'x' || flag == 'X')
		return (ft_put_in_hex(va_arg(args, unsigned int), flag));
	else if (flag == 'p')
	{
		a = va_arg(args, unsigned long long);
		if (a == 0)
			return (ft_putstr("(nil)"));
		return (ft_put_ptr(a));
	}
	return (0);
}

/*
	Prints something into the screen
*/
int	ft_printf(const char *str, ...)
{
	int		i;
	int		printed_length;
	va_list	args;

	i = 0;
	printed_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			printed_length += handle_conversions(str[i + 1], args);
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			printed_length += 1;
		}
		i++;
	}
	return (printed_length);
}
