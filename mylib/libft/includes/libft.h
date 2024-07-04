/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:23:22 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/02 19:59:26 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC,
	ENV_VAR,
}	t_token_type;

typedef struct s_node{
	t_token_type	type;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_node_d{
	int				data;
	struct s_node_d	*next;
	struct s_node_d	*prev;
}	t_node_d;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_str_numeric(char *str);

int			ft_toupper(int c);
int			ft_tolower(int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char *s1, char const *set);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_str_is_space(char *str);

void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memrchr(const void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);

char		**ft_split(char const *s, char c);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

t_node		*create_node(t_token_type type, char *value);
int			add_node_start(t_node **list, t_node *new);
t_node		*get_last_node(t_node *list);
int			add_to_back(t_node **list, t_node *new);
int			list_length(t_node *list);
t_node		*get_first_node(t_node *list);
t_node		*get_second_node(t_node *list);
int			remove_element(t_node **list);
int			reverse_ll(t_node **list);
int			shift_first(t_node **list);
int			shift_last(t_node **list);
int			pop(t_node **list);

t_node_d	*create_node_doubly(int data);
int			add_node_start_doubly(t_node_d **list, t_node_d *new);
t_node_d	*get_last_node_doubly(t_node_d *list);
int			add_to_back_doubly(t_node_d **list, t_node_d *new);
int			list_length_doubly(t_node_d *list);
t_node_d	*get_first_node_doubly(t_node_d *list);
t_node_d	*get_second_node_doubly(t_node_d *list);
int			remove_element_doubly(t_node_d **list);
int			reverse_ll_doubly(t_node_d **list);
int			shift_first_doubly(t_node_d **list);
int			shift_last_doubly(t_node_d **list);
int			pop_doubly(t_node_d **list);
int			ft_strcmp(char *s1, char *s2);

void		free_mtrxc(char **m);

#endif