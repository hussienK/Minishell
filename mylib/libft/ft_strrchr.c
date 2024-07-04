/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:50:48 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/10 14:46:12 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	int				i;

	i = 0;
	uc = (unsigned char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == uc)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
