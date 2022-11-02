/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:40:17 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/02 16:37:32 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

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
					ft_fprintf(2, "Quit: 3\n");
				g_gb.exit_statut = WTERMSIG(exit_value) + 128;
			}
			else
					g_gb.exit_statut = WEXITSTATUS(exit_value);
		}
	}
}

void	error_helper(t_execcmd *cmd)
{
	if (!access(cmd->argument[0], F_OK) && \
				access(cmd->argument[0], X_OK))
	{
		ft_fprintf(2, "Minishell: %s Permision denied\n", cmd->argument[0]);
		g_gb.exit_statut = 126;
	}
	else
	{
		ft_fprintf(2, "Minishell: %s No such file or directory\n",
			cmd->argument[0]);
		g_gb.exit_statut = 127;
	}
}

void	error_displayer(t_execcmd *cmd)
{
	if (ft_strchr(cmd->argument[0], '/'))
	{
		if (opendir(cmd->argument[0]))
		{
			ft_fprintf(2, "Minishell: %s is a directory\n", cmd->argument[0]);
			g_gb.exit_statut = 126;
		}
		else
			error_helper(cmd);
	}
	else
	{
		ft_fprintf(2, "Minishell: %s :command not found\n", cmd->argument[0]);
		g_gb.exit_statut = 127;
	}
	exit(g_gb.exit_statut);
}
