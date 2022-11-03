/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:59:57 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 06:14:28 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

int	valid_unset_name(char *var)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset_name_exist(char *var, t_senv **prenode)
{
	t_senv	*head;

	head = g_gb.env;
	while (head)
	{
		if (!ft_strcmp(head->key, var))
			return (1);
		*prenode = head;
		head = head->next;
	}
	return (0);
}

void	node_remover(t_senv *prenode, t_senv *node)
{
	if (!prenode)
	{
		node = g_gb.env;
		g_gb.env = g_gb.env->next;
	}
	else
	{
		node = prenode->next;
		prenode->next = node->next;
	}
	free(node->key);
	free(node->value);
	free(node);
}

void	unset_handler(char *var, int *exit_code, int *faila)
{
	t_senv	*prenode;
	t_senv	*tmp;

	tmp = NULL;
	prenode = 0;
	if (!valid_unset_name(var))
	{
		*faila = 1;
		if (!(*exit_code))
			(*exit_code)++;
		ft_putstr_fd("Minishell: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	if (unset_name_exist(var, &prenode))
		node_remover(prenode, tmp);
}

int	unset_cmd(char **args)
{
	int	i;
	int	exit_code;
	int	faila;

	faila = 0;
	if (!args[1])
		return (0);
	i = 1;
	exit_code = 0;
	while (args[i])
		unset_handler(args[i++], &exit_code, &faila);
	if (faila)
		g_gb.exit_statut = 1;
	else
		g_gb.exit_statut = 0;
	return (exit_code);
}
