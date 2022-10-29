/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:32:15 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/29 15:22:50 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

#define EXPORT_NO_EQUAL 0
#define EXPORT_ADD 1
#define EXPORT_REPLACE 2
#define EXPORT_APPEND 3

void	export_handler(char *var, int *exit_code, int *fail)
{
	int	mode;

	mode = 0;
	if (!valid_export_name(var, &mode))
	{
		*fail = 1;
		if (!(*exit_code))
			(*exit_code)++;
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	if (export_name_exist(var, &mode))
	{
		if (mode == EXPORT_NO_EQUAL)
			return ;
		if (mode == EXPORT_APPEND)
			export_append(var);
		else
			export_replace(var);
		return ;
	}
	export_add(var, mode);
}

void	export_declare(void)
{
	t_senv	*head;

	head = g_gb.env;
	while (head)
	{
		if (head->value)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
}

int	ft_export(char **args)
{
	int	i;
	int	exit_code;
	int	faila;

	faila = 0;
	if (!args[1])
	{
		export_declare();
		return (0);
	}
	i = 1;
	exit_code = 0;
	while (args[i])
		export_handler(args[i++], &exit_code, &faila);
	if (faila == 1)
		g_gb.exit_statut = 1;
	else
		g_gb.exit_statut = 0;
	return (exit_code);
}

void	export_add(char *var, int mode)
{
	char	*addr_var;
	char	*tmp;

	if (mode == EXPORT_NO_EQUAL || mode == EXPORT_REPLACE)
	{
		env_add_back(&g_gb.env, env_new(var));
		return ;
	}
	addr_var = ft_strchr(var, '+');
	*addr_var = 0;
	addr_var += 1;
	tmp = ft_strjoin(var, addr_var);
	env_add_back(&g_gb.env, env_new(tmp));
	free(tmp);
}
