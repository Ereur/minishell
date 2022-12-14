/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:08 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/29 15:14:24 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

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

int	check_new_line(char *str)
{
	int	i;

	if (str[0] != '-' || !str[1])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **av)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (av[i] && check_new_line(av[i]))
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
	g_gb.exit_statut = 0;
	return (0);
}
