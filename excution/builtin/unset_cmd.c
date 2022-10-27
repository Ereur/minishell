/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:59:57 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/21 12:07:35 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

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

void	unset_handler(char *var, int *exit_code)
{
	t_senv	*prenode;
	t_senv	*tmp;

	prenode = 0;
	if (!valid_unset_name(var))
	{
		if (!(*exit_code))
			(*exit_code)++;
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	if (unset_name_exist(var, &prenode))
	{
		tmp = prenode->next;
		prenode->next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	unset_cmd(char **args)
{
	int	i;
	int	exit_code;

	if (!args[1])
		return (0);
	i = 1;
	exit_code = 0;
	while (args[i])
		unset_handler(args[i++], &exit_code);
	return (exit_code);
}
