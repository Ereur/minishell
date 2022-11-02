/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:56:25 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/02 16:46:11 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_un(int fd, unsigned int nbr, int *len)
{
	if (nbr >= 10)
	{
		ft_putnbr(fd, nbr / 10, len);
		ft_putnbr(fd, nbr % 10, len);
	}
	else
	{
		nbr = nbr + '0';
		*len += ft_putchar(fd, nbr);
	}	
}

static int	ft_specificator(int fd, va_list ap, const char *str, int *len)
{
	if (str[0] == 'd')
		ft_putnbr(fd, va_arg(ap, int), len);
	else if (str[0] == 's')
		ft_putstr(fd, va_arg(ap, char *), len);
	else if (str[0] == 'c')
		*len += ft_putchar(fd, va_arg(ap, int));
	else if (str[0] == 'p')
		ft_put_p(fd, va_arg(ap, unsigned long), len);
	else if (str[0] == 'i')
		ft_putnbr(fd, va_arg(ap, int), len);
	else if (str[0] == 'u')
		ft_put_un(fd, va_arg(ap, unsigned int), len);
	else if (str[0] == 'x')
		ft_puthexa(fd, va_arg(ap, unsigned int), str[0], len);
	else if (str[0] == 'X')
		ft_puthexa(fd, va_arg(ap, unsigned int), str[0], len);
	else if (str[0] == '%')
		*len += ft_putchar(fd, str[0]);
	else
	{	
		*len += ft_putchar(fd, str[0]);
		return (0);
	}
	return (1);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	int		i;
	va_list	ap;
	int		len;

	len = 0;
	va_start (ap, str);
	while (*str)
	{
		i = 0;
		while (*str == '%')
		{	
			i = 0;
			if (*(++str) == 'p')
				ft_putstr(fd, "0x", &len);
			i = ft_specificator(fd, ap, str, &len);
			if (i)
				++str;
		}
		if (*str)
			len += ft_putchar(fd, *(str++));
	}
	va_end(ap);
	return (len);
}
