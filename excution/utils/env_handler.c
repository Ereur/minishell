/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:09:50 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/17 15:15:30 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	env_size()
{
	t_senv *head;
	int i;

	head = gb.env;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
	
}

t_senv	*env_grabber(char *keyword)
{
	t_senv *head;
	
	head = gb.env;

	while (head)
	{
		if (!ft_strcmp(keyword, head->key))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_senv	*env_new(char *str)
{
	t_senv *node;
	char	*sepp;

	node = (t_senv *)malloc(sizeof(t_senv));

	sepp = ft_strchr(str, '=');
	if (sepp)
	{
		*sepp = 0;
		node->key = ft_strdup(str);
		node->value = ft_strdup(sepp + 1);
		*sepp = '=';
	}
	else
	{
		node->key = ft_strdup(str);
		node->value = 0;
	}
	node->next = 0;
	return (node);

}

void	env_add_back(t_senv **env, t_senv *node)
{
	t_senv *head;
	
	if (!(*env))
	{
		*env = node;
		return ;
	}
	head = *env;
	while (head->next)
		head = head->next;
	head->next = node;
	
}

int track_env(char *keyword)
{
	t_senv *head;

	head = gb.env;

	while (head)
	{
		if (!ft_strcmp(head->key, keyword))
			return (1);
		head = head->next;
	}
	return (0);
}

void	setup_env(char **envp)
{
	int i;
	char	*tmp;

	i = 0;
	gb.env = 0;
	while (envp[i])
		env_add_back(&gb.env, env_new(envp[i++]));
	i = 0;
	if (!track_env("PWD"))
	{
		tmp = ft_strjoin("PWD=", getcwd(NULL, 0));
		if (tmp)
		{
			env_add_back(&gb.env, env_new(tmp));
			free(tmp);
		}
	}
	if (!track_env("SHLVL"))
	{
		tmp = ft_strdup("SHLVL=1");
		env_add_back(&gb.env, env_new(tmp));
		free(tmp);
	}
	if (!track_env("_"))
	{
		tmp = ft_strdup("_=/usr/bin/env");
		env_add_back(&gb.env, env_new(tmp));
		free(tmp);
	}	
	// get_envp();
}

void get_envp(void)
{
	int		i;
	char	*hold;
	char	*holdt;
	t_senv	*tmp;
	
	i = 0;

	tmp = gb.env;
	gb.envp = (char**)malloc(sizeof(char*) * (env_size() + 1));
	while (tmp)
	{
		// exit(1);
		hold = ft_strjoin(tmp->key,"=");
		holdt = ft_strjoin(hold,tmp->value);
		// free(hold);
		gb.envp[i] = holdt;
		// free(holdt);
		printf("%s \n", gb.envp[i]);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while(gb.envp[i])
	{
		free(gb.envp[i]);
		i++;
	}
	free(gb.envp);
	// print list
}