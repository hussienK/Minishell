/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:16:46 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/15 18:00:45 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strchr(const char *s, int c);
char	*ft_sstrjoin(char *s1, char *s2);
char	*ft_ssubstr(char *s, int start, size_t len);
char	*ft_sstrdup(char *str, int len);
int		ft_sstrlen(char *str);
int		is_full_line(char *str);
char	*seperate_line(char **saved_data);
char	*get_next_line(int fd);

#endif