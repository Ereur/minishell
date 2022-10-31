/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:09:50 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 09:23:30 by zoukaddo         ###   ########.fr       */
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

int	env_size(void)
{
	t_senv	*head;
	int		i;

	head = g_gb.env;
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
	t_senv	*head;

	head = g_gb.env;
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
	t_senv	*node;
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
	t_senv	*head;

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
