/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:55:38 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 08:43:51 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int fd, int c)
{
	write (fd, &c, 1);
	return (1);
}

void	ft_puthexa(int fd, unsigned int nb, char c, int *len)
{
	char			*base;

	base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_puthexa(fd, nb / 16, c, len);
		ft_puthexa(fd, nb % 16, c, len);
	}
	else
	{
		*len += ft_putchar(fd, base[nb]);
	}
}

void	ft_put_p(int fd, unsigned long nb, int *len)
{
	char			*base;

	base = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_put_p(fd, nb / 16, len);
		ft_put_p(fd, nb % 16, len);
	}
	else
	{
		*len += ft_putchar(fd, base[nb]);
	}
}

void	ft_putnbr(int fd, long long nb, int *len)
{
	size_t	nb2;

	if (nb < 0)
	{
		*len += ft_putchar(fd, '-');
		nb *= -1;
	}
	nb2 = nb;
	if (nb2 >= 10)
	{
		ft_putnbr(fd, nb2 / 10, len);
		ft_putnbr(fd, nb2 % 10, len);
	}
	else
	{
		nb2 = nb2 + '0';
		*len += ft_putchar(fd, nb2);
	}
}

void	ft_putstr(int fd, char *str, int *len)
{
	int	i;

	i = 0;
	if (!str)
	{	
		ft_putstr(fd, "(null)", len);
		return ;
	}
	while (str[i] != 0)
	{
		*len += ft_putchar(fd, str[i]);
		i++;
	}
}
