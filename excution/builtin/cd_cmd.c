/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 06:55:36 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

void	mod_set_pwd(int *mod)
{
	char	*tmp;
	char	*hold;

	hold = NULL;
	tmp = NULL;
	if (mod)
	{
		hold = getcwd(NULL, 0);
		tmp = ft_strjoin("PWD=", hold);
		ft_free(&hold);
	}
	else
	{
		hold = getcwd(NULL, 0);
		tmp = ft_strjoin("OLDPWD=", hold);
		ft_free(&hold);
	}
	if (!tmp)
		return ;
	env_add_back(&g_gb.env, env_new(tmp));
	free(tmp);
}

void	set_pwd(t_senv *pwd, int mod)
{
	if (pwd)
	{
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
	else
		mod_set_pwd(&mod);
}

int	check_home(void)
{
	t_senv	*home;

	home = env_grabber("HOME");
	if (!home)
	{
		g_gb.exit_statut = 1;
		ft_putstr_fd("Minishell: cd : HOME not set\n", 2);
		return (1);
	}
	if (chdir(home->value))
	{
		g_gb.exit_statut = 1;
		ft_putstr_fd("Minishell: cd : ", 2);
		ft_putstr_fd(home->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	cd_cmd(char **argument)
{
	set_pwd(env_grabber("OLDPWD"), 0);
	if (!argument[1])
	{
		check_home();
		return (1);
	}
	if (chdir(argument[1]))
	{
		g_gb.exit_statut = 1;
		ft_putstr_fd("Minishell: cd : ", 2);
		ft_putstr_fd(argument[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	set_pwd(env_grabber("PWD"), 1);
	g_gb.exit_statut = 0;
	if (argument[1][0] == '.' && !argument[1][1])
		return (1);
	return (0);
}
