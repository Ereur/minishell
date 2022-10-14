/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:07:11 by zoukaddo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/12 00:26:00 by aamoussa         ###   ########.fr       */
=======
/*   Updated: 2022/10/14 09:45:54 by zoukaddo         ###   ########.fr       */
>>>>>>> 2a5cadd44e1dbc5ef653c596e194b57119f7921c
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	rl_replace_line(const char *text, int clear_undo);

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
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