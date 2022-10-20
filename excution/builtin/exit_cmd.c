/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:05:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/19 00:52:23 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

#define EXIT_SUC 0
#define EXIT_FAIL 1
#define EXIT_FAIL_DOUBLE 2

// fail double joj na9is

int	exit_atoi(const char *str, int *mod)
{
	int				i;
	unsigned long	num;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	if (!ft_strcmp(str, "--"))
	{
		*mod = EXIT_FAIL_DOUBLE;
		return (0);
	}
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (!ft_isdigit(str[i]) && !(str[i + 1]))
	{
		*mod = EXIT_FAIL;
		return (0);
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		*mod = EXIT_FAIL;
		if (num > LONG_MAX)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		num = num * 10 + (str[i++] - '0');
	}
	if (str[i])
	{
		*mod = EXIT_FAIL;
		return (0);
	}
	*mod = EXIT_SUC;
	return ((int)num * sign);
}

void	numeric_argument_required(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	exit_cmd(char **args)
{
	int	exit_num;
	int	mod;

	mod = EXIT_SUC;
	if (!args[1])
		exit(gb.exit_statut);
	if (args[2])
	{
		exit_num = exit_atoi(args[1], &mod);
		if (mod == EXIT_FAIL_DOUBLE)
		{
			if (args[2])
			{
				exit_num = exit_atoi(args[2], &mod);
				if (mod > 0)
					numeric_argument_required(args[2]);
				exit(exit_num);
			}
			exit(gb.exit_statut);
		}
		if (mod == EXIT_FAIL)
			numeric_argument_required(args[1]);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_num = exit_atoi(args[1], &mod);
	if (mod == EXIT_FAIL)
		numeric_argument_required(args[1]);
	if (mod == EXIT_SUC)
		exit(exit_num);
	exit(gb.exit_statut);
}
