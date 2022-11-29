/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:07:11 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 07:56:10 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_gb.exit_statut = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	print_er(char *s)
{
	ft_putstr_fd("Minishell :", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	g_gb.exit_statut = 127;
}
