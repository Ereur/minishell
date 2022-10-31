/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:05:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 14:52:11 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

#define EXIT_SUC 0
#define EXIT_FAIL 1
#define EXIT_FAIL_DOUBLE 2

int	atoi_norm(const char *str, t_cord *cord, int sign)
{
	while (str[cord->i] && str[cord->i] >= '0' && str[cord->i] <= '9')
	{
		cord->mod = EXIT_FAIL;
		if (cord->num > LONG_MAX)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		cord->num = cord->num * 10 + (str[cord->i++] - '0');
	}
	if (str[cord->i])
	{
		cord->mod = EXIT_FAIL;
		return (0);
	}
	cord->mod = EXIT_SUC;
	return (0);
}

int	exit_atoi(const char *str, t_cord *cord)
{
	int				sign;

	cord->i = 0;
	cord->num = 0;
	sign = 1;
	if (!ft_strcmp(str, "--"))
	{
		cord->mod = EXIT_FAIL_DOUBLE;
		return (0);
	}
	while ((str[cord->i] >= '\t' && str[cord->i] <= '\r')
		|| str[cord->i] == ' ')
		cord->i++;
	if (str[cord->i] == '-')
		sign = -1;
	if (!ft_isdigit(str[cord->i]) && !(str[cord->i + 1]))
	{
		cord->mod = EXIT_FAIL;
		return (0);
	}
	if (str[cord->i] == '-' || str[cord->i] == '+')
		cord->i++;
	atoi_norm(str, cord, sign);
	return ((int)cord->num * sign);
}

void	numeric_argument_required(char *arg)
{
	ft_fprintf(2, "Minishell: exit: %s: numeric argument required\n", arg);
	exit(255);
}

void	exit_cmd_norm(char **args, t_cord *cord, int exit_num)
{
	if (cord->mod == EXIT_FAIL_DOUBLE)
	{
		if (args[2])
		{
			exit_num = exit_atoi(args[2], cord);
			if (cord->mod > 0)
				numeric_argument_required(args[2]);
			printf("exit\n");
			exit(exit_num);
		}
		exit(g_gb.exit_statut);
	}
	if (cord->mod == EXIT_FAIL)
		numeric_argument_required(args[1]);
	ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
}

int	exit_cmd(char **args)
{
	int		exit_num;
	t_cord	cord;

	cord.mod = EXIT_SUC;
	if (!args[1])
		exit(g_gb.exit_statut);
	if (args[2])
	{
		exit_num = exit_atoi(args[1], &cord);
		exit_cmd_norm(args, &cord, exit_num);
		return (1);
	}
	exit_num = exit_atoi(args[1], &cord);
	if (cord.mod == EXIT_FAIL)
		numeric_argument_required(args[1]);
	if (cord.mod == EXIT_SUC)
	{
		printf("exit\n");
		exit(exit_num);
	}
	exit(g_gb.exit_statut);
}
