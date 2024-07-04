/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:11:44 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/10 14:55:01 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*a;
	char		*b;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	a = (char *) src;
	b = (char *) dest;
	i = 0;
	if (b > a)
		while (n-- > 0)
			b[n] = a[n];
	else
	{
		while (i < n)
		{
			b[i] = a[i];
			i++;
		}
	}
	return (dest);
}
