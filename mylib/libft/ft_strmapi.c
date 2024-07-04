/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:07:32 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/12 19:52:01 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_strs(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ans;

	if (!s)
		return (NULL);
	ans = create_strs(ft_strlen(s));
	if (!ans)
		return (NULL);
	i = 0;
	ans[ft_strlen(s)] = '\0';
	while (s[i])
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	return (ans);
}
