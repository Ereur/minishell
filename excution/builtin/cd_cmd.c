/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/21 12:07:35 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

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

int	cd_cmd(char **argument)
{
	t_senv	*home;

	set_pwd(env_grabber("OLDPWD"), 0);
	if (!argument[1])
	{
		g_gb.exit_statut = 1;
		home = env_grabber("HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		if (chdir(home->value))
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(home->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		return (1);
	}
	if (chdir(argument[1]))
	{
		g_gb.exit_statut = 1;
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(argument[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	set_pwd(env_grabber("PWD"), 1);
	// g_gb.exit_statut = 0;
	return (0);
}
