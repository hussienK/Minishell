/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:01:34 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/15 19:04:08 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_sstrlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_sstrdup(char *str, int len)
{
	char	*array;
	int		count;

	if (!str || !len)
		return (NULL);
	count = -1;
	array = (char *)malloc((len + 1) * sizeof(char));
	while (++count < len)
		array[count] = str[count];
	array[count] = '\0';
	return (array);
}

char	*ft_ssubstr(char *s, int start, size_t len)
{
	char		*ans;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	else if (start >= ft_sstrlen(s))
		len = 0;
	if (len > (size_t)ft_sstrlen(s) - start)
		len = ft_sstrlen(s) - start;
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

char	*ft_sstrjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		sizes;
	size_t		k;
	char		*ans;

	i = 0;
	if (!s1)
		return (ft_sstrdup(s2, ft_sstrlen(s2)));
	sizes = ft_sstrlen(s1) + ft_sstrlen(s2);
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
		ans[k++] = s2[i++];
	free(s1);
	return (ans);
}

char	*ft_sstrchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if (*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}	
