/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:25 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/10 17:47:47 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ans;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	else if (start >= ft_strlen(s))
		len = 0;
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	ans[len] = '\0';
	while (i < len)
	{
		ans[i] = s[start];
		start++;
		i++;
	}
	return (ans);
}
