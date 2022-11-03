/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:54:48 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 04:06:56 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

#define EXPORT_NO_EQUAL 0
#define EXPORT_ADD 1
#define EXPORT_REPLACE 2
#define EXPORT_APPEND 3

int	valid_export_name(char *var, int *mode)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i])
	{
		if (var[i] == '+' && var[i + 1] == '=')
		{
			*mode = EXPORT_APPEND;
			return (1);
		}
		if (var[i] == '=')
		{
			*mode = EXPORT_REPLACE;
			return (1);
		}
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	free_newvar(char *new_var)
{
	t_senv	*head;

	head = g_gb.env;
	while (head)
	{
		if (!ft_strcmp(head->key, new_var))
		{
			free(new_var);
			return (1);
		}
		head = head->next;
	}
	free(new_var);
	return (0);
}

int	export_name_exist(char *var, int *mode)
{
	char	*addr_var;
	char	*new_var;

	new_var = ft_strdup(var);
	addr_var = ft_strchr(new_var, '=');
	if (addr_var)
	{
		if (*(addr_var - 1) == '+')
		{
			*(addr_var - 1) = 0;
			*mode = EXPORT_APPEND;
		}
		else
		{
			*(addr_var) = 0;
			*mode = EXPORT_REPLACE;
		}
	}
	else
		*mode = EXPORT_NO_EQUAL;
	if (free_newvar(new_var) == 1)
		return (1);
	return (0);
}

void	export_append(char *var)
{
	t_senv	*head;
	char	*addr_var;
	char	*tmp;

	head = g_gb.env;
	addr_var = ft_strchr(var, '+');
	*addr_var = 0;
	addr_var += 2;
	while (head)
	{
		if (!ft_strcmp(head->key, var))
		{
			tmp = head->value;
			if (!tmp)
				tmp = ft_strdup("");
			head->value = ft_strjoin(tmp, addr_var);
			free(tmp);
			return ;
		}
		head = head->next;
	}
}

void	export_replace(char *var)
{
	t_senv	*head;
	char	*addr_var;
	char	*tmp;

	head = g_gb.env;
	addr_var = ft_strchr(var, '=');
	*addr_var = 0;
	addr_var += 1;
	while (head)
	{
		if (!ft_strcmp(head->key, var))
		{
			tmp = head->value;
			head->value = ft_strdup(addr_var);
			free(tmp);
			return ;
		}
		head = head->next;
	}
}
