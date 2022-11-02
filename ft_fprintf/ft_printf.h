/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:56:06 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 08:59:56 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_putchar(int fd, int c);
void	ft_putnbr(int fd, long long nb, int *len);
void	ft_putstr(int fd, char *str, int *len);
void	ft_puthexa(int fd, unsigned int nb, char c, int *len);
int		ft_fprintf(int fd, const char *str, ...);
void	ft_put_p(int fd, unsigned long nb, int *len);
#endif