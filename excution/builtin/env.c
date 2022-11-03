/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:58:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 06:12:02 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

void	env(char **arg)
{
	t_senv	*head;

	if (arg[1])
	{
		g_gb.exit_statut = 1;
		ft_putstr_fd("env :", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
