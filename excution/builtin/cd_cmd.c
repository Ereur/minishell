/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 09:41:27 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

void	set_pwd(t_senv *pwd, int mod)
{
	char	*tmp;

	if (pwd)
	{
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
	else
	{
		if (mod)
			tmp = ft_strjoin("PWD=", getcwd(NULL, 0));
		else
			tmp = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
		if (!tmp)
			return ;
		env_add_back(&g_gb.env, env_new(tmp));
		free(tmp);
	}
}

int	check_home(char **argument)
{
	t_senv	*home;

	home = env_grabber("HOME");
	if (!home)
	{
		g_gb.exit_statut = 1;
		ft_fprintf(2, "Minishell: cd : HOME not set\n");
		return (1);
	}
	if (chdir(home->value))
	{
		g_gb.exit_statut = 1;
		ft_fprintf(2, "Minishell: cd: %s: No such file or directory\n",
			home->value);
		return (1);
	}
	return (0);
}

int	cd_cmd(char **argument)
{
	t_senv	*home;

	set_pwd(env_grabber("OLDPWD"), 0);
	if (!argument[1])
	{
		check_home(argument);
		return (1);
	}
	if (chdir(argument[1]))
	{
		g_gb.exit_statut = 1;
		ft_fprintf(2, "Minishell: cd: %s: No such file or directory\n",
			argument[1]);
		return (1);
	}
	set_pwd(env_grabber("PWD"), 1);
	g_gb.exit_statut = 0;
	if (argument[1][0] == '.' && !argument[1][1])
		return (1);
	return (0);
}
