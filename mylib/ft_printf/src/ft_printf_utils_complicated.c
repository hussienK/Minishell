/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_complicated.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:54:14 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/12 14:41:34 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_length(unsigned int nb)
{
	unsigned int	n;

	n = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		n++;
	}
	return (n);
}

char	*ft_atoi_hex(unsigned int nb, char format)
{
	char	*base;
	char	*ans;
	int		len;

	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	len = get_length(nb);
	ans = (char *)malloc(sizeof(char) * (len + 1));
	ans[len] = '\0';
	if (nb == 0)
	{
		ans[0] = '0';
		return (ans);
	}
	len--;
	while (nb > 0)
	{
		ans[len--] = base[nb % 16];
		nb /= 16;
	}
	return (ans);
}

int	ft_put_in_hex(unsigned int hex, int format)
{
	char	*ans;
	int		i;

	ans = ft_atoi_hex(hex, format);
	i = ft_putstr(ans);
	free(ans);
	return (i);
}
