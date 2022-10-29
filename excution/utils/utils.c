/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:40:17 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/28 12:42:13 by zoukaddo         ###   ########.fr       */
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
		if (catch_last_pid == gb.last_pid)
		{
			if (WIFSIGNALED(exit_value))
			{
				if (WTERMSIG(exit_value) == 3)
					printf("Quit: 3\n");
				gb.exit_statut = WTERMSIG(exit_value) + 128;
			}
			else
					gb.exit_statut = WEXITSTATUS(exit_value);
		}
	}
}

void	error_helper(t_execcmd *cmd)
{
	if (!access(cmd->argument[0], F_OK) && \
				access(cmd->argument[0], X_OK))
	{
		ft_putstr_fd(": Permision denied\n", 2);
		gb.exit_statut = 126;
	}
	else
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		gb.exit_statut = 127;
	}
}

void	error_displayer(t_execcmd *cmd)
{
	if (ft_strchr(cmd->argument[0], '/'))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->argument[0], 2);
		if (opendir(cmd->argument[0]))
		{
			ft_putstr_fd(": is a directory\n", 2);
			gb.exit_statut = 126;
		}
		else
			error_helper(cmd);
	}
	else
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->argument[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		gb.exit_statut = 127;
	}
	exit(gb.exit_statut);
}
