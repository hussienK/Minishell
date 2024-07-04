/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:49:23 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/10 16:52:53 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*ans;

	size = ft_strlen(s);
	ans = (char *)malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (NULL);
	ans[size] = '\0';
	i = 0;
	while (s[i])
	{
		ans[i] = s[i];
		i++;
	}
	return (ans);
}
