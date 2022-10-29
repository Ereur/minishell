/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:25:17 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/28 12:03:58 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	redirection_built(t_execcmd *cmd)
{
	int	fd;

	if (cmd->input > 0)
	{
		gb.input = dup(0);
		if (dup2(cmd->input, 0) == -1)
		{
			perror("dup filed :");
			exit(1);
		}
		close(cmd->input);
	}
	if (cmd->output > 1)
	{
		gb.output = dup(1);
		dup2(cmd->output, 1);
		close(cmd->output);
	}
}

void	exitcodesandwait(void)
{
	int			exit_value;

	exit_value = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(&exit_value);
	if (WIFSIGNALED(exit_value))
	{
		if (WTERMSIG(exit_value) == 3)
			printf("Quit: 3\n");
		gb.exit_statut = WTERMSIG(exit_value) + 128;
	}
	else if (WIFEXITED(exit_value))
		gb.exit_statut = WEXITSTATUS(exit_value);
}

void	dupandclosefds(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	dup2(gb.output, 1);
	dup2(gb.input, 0);
	if (gb.input != 0)
		close(gb.input);
	if (gb.output != 1)
		close(gb.output);
}

void	execute_builtins(t_cmd *cmd)
{
	int			pipe[2];
	t_execcmd	*exec;
	t_redircmd	*redir;
	t_pipecmd	*pipecmd;
	int			exit_value;

	exit_value = 0;
	if (cmd->type == EXEC)
	{
		exec = (t_execcmd *)(cmd);
		if (exec->input > 0 || exec->output > 1)
			redirection_built(exec);
		if (exec->input == -1 || exec->output == -1)
			return ;
		if (checifbuiltin(exec))
		{
			if (my_fork() == 0)
				execute_cmd(exec);
			exitcodesandwait();
		}
		dupandclosefds();
	}
}
