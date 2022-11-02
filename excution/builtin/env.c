/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:58:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 09:54:12 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

void	env(char **arg)
{
	t_senv	*head;

	if (arg[1])
	{
		g_gb.exit_statut = 1;
		ft_fprintf(2, "env: %s: No such file or directory\n", arg[1]);
		return ;
	}
	head = g_gb.env;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	g_gb.exit_statut = 0;
	return ;
}
