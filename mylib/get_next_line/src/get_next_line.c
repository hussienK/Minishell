/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:15:07 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/15 18:01:44 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	checks if a given string is a full line to be returned
*/
int	is_full_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
 * takes the saved data and returns the first line from it
  after removing this line from the saved data
*/
char	*seperate_line(char **saved_data)
{
	char	*ans;
	char	*temp;
	size_t	i;

	i = 0;
	if (!(*saved_data))
		return (NULL);
	temp = *saved_data;
	while (temp[i] != '\n' && temp[i])
		i++;
	if (temp[i] == '\n')
		i++;
	ans = ft_sstrdup(temp, i);
	*saved_data = ft_sstrdup(temp + i, ft_sstrlen(temp + i));
	if (temp)
		free(temp);
	temp = NULL;
	return (ans);
}

char	*get_next_line(int fd)
{
	static char	*saved_data;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (free(saved_data), saved_data = NULL, NULL);
	if (is_full_line(saved_data))
		return (seperate_line(&saved_data));
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(saved_data), free(buffer), saved_data = NULL, NULL);
		buffer[bytes_read] = '\0';
		saved_data = ft_sstrjoin(saved_data, buffer);
		if (is_full_line(saved_data))
			break ;
	}
	if (buffer)
		free(buffer);
	return (seperate_line(&saved_data));
}
