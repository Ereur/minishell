/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 22:53:43 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/29 15:14:24 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	track_env(char *keyword)
{
	t_senv	*head;

	head = g_gb.env;
	while (head)
	{
		if (!ft_strcmp(head->key, keyword))
			return (1);
		head = head->next;
	}
	return (0);
}

void	track(char *tmp)
{
	if (!track_env("SHLVL"))
	{
		tmp = ft_strdup("SHLVL=1");
		env_add_back(&g_gb.env, env_new(tmp));
		free(tmp);
	}
	if (!track_env("_"))
	{
		tmp = ft_strdup("_=/usr/bin/env");
		env_add_back(&g_gb.env, env_new(tmp));
		free(tmp);
	}
}

void	setup_env(char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	g_gb.env = 0;
	while (envp[i])
		env_add_back(&g_gb.env, env_new(envp[i++]));
	i = 0;
	if (!track_env("PWD"))
	{
		tmp = ft_strjoin("PWD=", getcwd(NULL, 0));
		if (tmp)
		{
			env_add_back(&g_gb.env, env_new(tmp));
			free(tmp);
		}
	}
	track(tmp);
	get_envp();
}

void	get_envp(void)
{
	int		i;
	char	*hold;
	char	*holdt;
	t_senv	*tmp;

	i = 0;
	tmp = g_gb.env;
	if (g_gb.envp)
		free(g_gb.envp);
	g_gb.envp = (char **)malloc(sizeof(char *) * (env_size() + 1));
	while (tmp)
	{
		hold = ft_strjoin(tmp->key, "=");
		holdt = ft_strjoin(hold, tmp->value);
		ft_free(&hold);
		g_gb.envp[i] = holdt;
		tmp = tmp->next;
		i++;
	}
	g_gb.envp[i] = 0;
}
