/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 08:53:00 by hkanaan           #+#    #+#             */
/*   Updated: 2024/06/18 12:02:50 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_printf(const char *str, ...);
int	ft_putnbr(int n);
int	ft_putunsigned_nb(unsigned int n);
int	ft_putpercent(void);
int	ft_sstrlen_p(char *s);
int	ft_put_in_hex(unsigned int hex, int format);
int	ft_put_ptr(unsigned long long nb);

#endif
