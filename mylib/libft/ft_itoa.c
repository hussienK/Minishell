/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:02:08 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/11 19:44:18 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

char	*create(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

int	real_number(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

long long	abs_val(long long n)
{
	long long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

int	get_i(int sign, char **str)
{
	int	i;

	i = 0;
	if (sign)
	{
		*(*str) = '-';
		i = 1;
	}
	else
		i = 0;
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	int				i;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = real_number(n);
	str = create(len);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	nbr = abs_val(n);
	i = get_i(sign, &str);
	while (len >= i)
	{
		str[len--] = 48 + nbr % 10;
		nbr /= 10;
	}
	return (str);
}
