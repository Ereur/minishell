/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:25:17 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/09 23:30:27 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	redirection_built(t_execcmd *cmd)
{
	int fd;

	if (cmd->input != -1)
	{
		gb.input = dup(0);
		dup2(cmd->input, 0);
		close(cmd->input);
	}
	if (cmd->output != -1)
	{
		gb.output = dup(1);
		dup2(cmd->output, 1);
		close(cmd->output);
	}
}

void execute_builtins(t_cmd *cmd)
{
	int			pipe[2];
	t_execcmd	*exec;
	t_redircmd	*redir;
	t_pipecmd	*pipecmd;

	if (cmd->type == EXEC)
	{
		exec = (t_execcmd *)(cmd);
		if (checifbuiltin(exec))
		{
			if (exec->input != -1 || exec->output != 1)
				redirection_built(exec);
			if (my_fork() == 0)
				execute_cmd(exec);
			wait(NULL);
		}
		// printf("%d\n",gb.output);
		// printf("%d\n",gb.input);
		dup2(gb.output, 1);
		dup2(gb.input, 0);
		if (gb.input != 0)
			close(gb.input);
		if (gb.output != 1)
			close(gb.output);
		// close(gb.output);
		// close(gb.input);
	}
	// if (cmd->type == REDIR)
	// {
	// 	redir = (t_redircmd *)(cmd);
	// 	redirection_built(redir);
	// 	execute_builtins(redir->cmd);
	// }
}