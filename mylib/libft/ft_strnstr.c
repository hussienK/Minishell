/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:06:36 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/10 16:47:37 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (!big && !len)
		return (NULL);
	if (*little == '\0')
		return ((char *) big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		k = i;
		while (big[k] == little[j] && k < len && little[j])
		{
			if (little[j + 1] == '\0' && k < len)
				return ((char *)big + i);
			k++;
			j++;
		}
		i++;
	}
	return (NULL);
}
