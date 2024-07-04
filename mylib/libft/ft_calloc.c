/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:13:59 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/16 09:16:29 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ans;

	if (nmemb && size && nmemb > (UINT_MAX / size))
		return (NULL);
	ans = malloc(size * nmemb);
	if (!ans)
		return (NULL);
	ans = ft_memset(ans, 0, nmemb * size);
	return (ans);
}
