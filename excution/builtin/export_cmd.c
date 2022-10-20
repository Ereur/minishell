/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:54:48 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/19 00:37:46 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

# define EXPORT_NO_EQUAL 0
# define EXPORT_ADD 1
# define EXPORT_REPLACE 2
# define EXPORT_APPEND 3

int valid_export_name(char *var, int *mode)
{
	int i;

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

int	export_name_exist(char *var, int *mode)
{
	t_senv *head;
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
	head = gb.env;
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

void	export_append(char *var)
{
	t_senv	*head;
	char	*addr_var;
	char	*tmp;

	head = gb.env;
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

	head = gb.env;
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

void	export_add(char *var, int mode)
{
	char	*addr_var;
	char	*tmp;

	if (mode == EXPORT_NO_EQUAL || mode == EXPORT_REPLACE)
	{
		env_add_back(&gb.env, env_new(var));
		return ;
	}
	addr_var = ft_strchr(var, '+');
	*addr_var = 0;
	addr_var += 1;
	tmp = ft_strjoin(var, addr_var);
	env_add_back(&gb.env, env_new(tmp));
	free(tmp);
}

void	export_handler(char *var, int *exit_code)
{
	int	mode;

	mode = 0;
	if (!valid_export_name(var, &mode))
	{
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
	/* linked list should be sorted to be displayed */
	// sort linked list by the key alphabetically
	head = gb.env;
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

	if (!args[1])
	{
		export_declare();
		return (0);
	}
	i = 1;
	exit_code = 0;
	while (args[i])
		export_handler(args[i++], &exit_code);

	return (exit_code);
}
