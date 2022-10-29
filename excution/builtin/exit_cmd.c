/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:05:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/29 15:19:15 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

#define EXIT_SUC 0
#define EXIT_FAIL 1
#define EXIT_FAIL_DOUBLE 2

// fail double joj na9is
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

// int	exit_atoi(const char *str, int *mod)
// {
// 	int				i;
// 	unsigned long	num;
// 	int				sign;
// 	t_cord			cord;

// 	i = 0;
// 	num = 0;
// 	sign = 1;
// 	if (!ft_strcmp(str, "--"))
// 	{
// 		*mod = EXIT_FAIL_DOUBLE;
// 		return (0);
// 	}
// 	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
// 		i++;
// 	if (str[i] == '-')
// 		sign = -1;
// 	if (!ft_isdigit(str[i]) && !(str[i + 1]))
// 	{
// 		*mod = EXIT_FAIL;
// 		return (0);
// 	}
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	// atoi_norm(str, mod, &cord, sign);
// 	while (str[i] && str[i] >= '0' && str[i] <= '9')
// 	{
// 		*mod = EXIT_FAIL;
// 		if (num > LONG_MAX)
// 		{
// 			if (sign == 1)
// 				return (-1);
// 			return (0);
// 		}
// 		num = num * 10 + (str[i++] - '0');
// 	}
// 	if (str[i])
// 	{
// 		*mod = EXIT_FAIL;
// 		return (0);
// 	}
// 	*mod = EXIT_SUC;
// 	return ((int)num * sign);
// }
void	numeric_argument_required(char *arg)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
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
		exit(exit_num);
	exit(g_gb.exit_statut);
}

// int	exit_cmd(char **args)
// {
// 	int		exit_num;
// 	int		mod;
// 	t_cord	cord;

// 	mod = EXIT_SUC;
// 	if (!args[1])
// 		exit(g_gb.exit_statut);
// 	if (args[2])
// 	{
// 		exit_num = exit_atoi(args[1], &mod);
// 		if (mod == EXIT_FAIL_DOUBLE)
// 		{
// 			if (args[2])
// 			{
// 				exit_num = exit_atoi(args[2], &mod);
// 				if (mod > 0)
// 					numeric_argument_required(args[2]);
// 				exit(exit_num);
// 			}
// 			exit(g_gb.exit_statut);
// 		}
// 		if (mod == EXIT_FAIL)
// 			numeric_argument_required(args[1]);
// 		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
// 		return (1);
// 	}
// 	exit_num = exit_atoi(args[1], &mod);
// 	if (mod == EXIT_FAIL)
// 		numeric_argument_required(args[1]);
// 	if (mod == EXIT_SUC)
// 		exit(exit_num);
// 	exit(g_gb.exit_statut);
// }
