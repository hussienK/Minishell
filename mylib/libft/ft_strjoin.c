/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:48:43 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/10 17:54:38 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		sizes;
	size_t		k;
	char		*ans;

	i = 0;
	sizes = ft_strlen(s1) + ft_strlen(s2);
	ans = (char *)malloc(sizeof(char) * (sizes + 1));
	if (!ans)
		return (NULL);
	ans[sizes] = '\0';
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	k = i;
	i = 0;
	while (s2[i])
	{
		ans[k] = s2[i];
		i++;
		k++;
	}
	return (ans);
}
