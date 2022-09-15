/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:08 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/15 18:01:26 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

int ft_strlen(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void    ft_echo(char **av)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (av[i] && strcmp(av[i], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
}

int     main(int ac, char **av)
{
    ft_echo(av);
    return (0);
}
