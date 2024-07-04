/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:56:04 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/01 18:23:58 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t		size;
	size_t		start;
	size_t		i;
	char		*ans;

	if (!s1 || !set)
		return (NULL);
	size = ft_strlen(s1);
	while (size > 0 && is_in_set(s1[size - 1], set))
		size--;
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	if (start >= size)
		return (ft_strdup(""));
	ans = (char *)malloc(sizeof(char) * (size - start + 1));
	if (!ans)
		return (NULL);
	ans[size - start] = '\0';
	i = 0;
	while (start < size)
		ans[i++] = s1[start++];
	free(s1);
	return (ans);
}
