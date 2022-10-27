/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:40:17 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/21 12:07:35 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

pid_t	my_fork(void)
{
	pid_t	i;

	i = fork();
	if (i < 0)
	{
		perror("error");
		exit(1);
	}
	return (i);
}

void	waitforcprocess(void)
{
	int	catch_last_pid;
	int	exit_value;

	exit_value = 0;
	catch_last_pid = 1;
	while (catch_last_pid != -1)
	{
		catch_last_pid = waitpid(-1, &exit_value, 0);
		if (catch_last_pid == g_gb.last_pid)
		{
			if (WIFSIGNALED(exit_value))
			{
				if (WTERMSIG(exit_value) == 3)
					printf("Quit: 3\n");
				g_gb.exit_statut = WTERMSIG(exit_value) + 128;
			}
			else
					g_gb.exit_statut = WEXITSTATUS(exit_value);
		}
	}
}
