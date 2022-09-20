/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:25:17 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/20 21:14:34 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	redirection_built(t_redircmd *redir)
{
	int fd;

	if (redir->fd == 0)
	{
		gb.input = dup(0);
		fd = open(redir->filee->content, redir->mode, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", redir->filee->content);
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (redir->fd == 1)
	{
		gb.output = dup(1);
		fd = open(redir->filee->content, redir->mode, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", redir->filee->content);
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
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
		checifbuiltin(exec);
		dup2(gb.output, 1);
		dup2(gb.input, 0);
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redircmd *)(cmd);
		redirection_built(redir);
		execute_builtins(redir->cmd);
	}
}