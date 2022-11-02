/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:21:46 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 00:14:56 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/execution.h"
#include "../parser/parser.h"

void	close_all_fds(t_cmd *cmd)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)(cmd);
	if (cmd->type == PIPE)
	{
		close_all_fds(pipecmd->left);
		close_all_fds(pipecmd->right);
	}
	if (cmd->type == EXEC)
	{
		if (((t_execcmd *)cmd)->input != 0)
			close(((t_execcmd *)cmd)->input);
		if (((t_execcmd *)cmd)->output != 1)
			close(((t_execcmd *)cmd)->output);
	}
}

void	child_process(t_cmd *first_cmd, t_execcmd *cmd, t_cord *cord, int *fd)
{
	if (g_gb.here_doc == 1)
		exit(1);
	if (cmd->input < 0 || cmd->output < 0)
		exit(1);
	if (cmd->input != 0)
		dup2(cmd->input, 0);
	else
		dup2(g_gb.fd_input_prev, 0);
	if (cmd->output != 1)
		dup2(cmd->output, 1);
	else if (cord->cpipe < cord->npipe)
	{
		dup2(fd[1], 1);
	}
	close_all_fds(first_cmd);
	close(fd[0]);
	close(fd[1]);
	if (checifbuiltin(cmd) == 0)
		;
	else
		execute_cmd(cmd);
	exit(g_gb.exit_statut);
}

pid_t	exec_command(t_cmd *first_cmd, t_execcmd *cmd, int npipe, int cpipe)
{
	int		fd[2];
	pid_t	pid;
	t_cord	cord;

	cord.npipe = npipe;
	cord.cpipe = cpipe;
	pipe(fd);
	pid = my_fork();
	if (!pid)
		child_process(first_cmd, cmd, &cord, fd);
	close(fd[1]);
	if (g_gb.fd_input_prev != 0)
		close(g_gb.fd_input_prev);
	g_gb.fd_input_prev = fd[0];
	return (pid);
}

void	pipe_executer(t_cmd *first_cmd, t_cmd *cmd, int npipe, int cpipe)
{
	t_pipecmd	*pipecmd;
	int			i;
	int			pid;

	i = 0;
	pipecmd = (t_pipecmd *)(cmd);
	if (!cmd)
		return ;
	if (cmd->type == PIPE)
	{
		pipe_executer(first_cmd, pipecmd->left, npipe, cpipe);
		pipe_executer(first_cmd, pipecmd->right, npipe, cpipe + 1);
	}
	if (cmd->type == EXEC)
		g_gb.last_pid = exec_command(first_cmd, (t_execcmd *)cmd, npipe, cpipe);
}

int	checkbuiltprotection(t_execcmd *exec)
{
	if (!(exec->argument))
	{
		g_gb.exit_statut = 0;
		return (1);
	}
	if (!(exec->argument[0]))
	{
		g_gb.exit_statut = 0;
		return (1);
	}
	return (0);
}
