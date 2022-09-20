/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:08:23 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/20 03:35:58 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	checifbuiltin(t_execcmd *exec)
{
	if (ft_strcmp(exec->argument[0], "cd") == 0)
			cd_cmd(exec->argument);
	if (ft_strcmp(exec->argument[0], "pwd") == 0)
			built_in_pwd(exec->argument);
	if (ft_strcmp(exec->argument[0], "env") == 0)
			env();
	if (ft_strcmp(exec->argument[0], "echo") == 0)
			ft_echo(exec->argument);
	if (ft_strcmp(exec->argument[0], "export") == 0)
			ft_export(exec->argument);
	if (ft_strcmp(exec->argument[0], "unset") == 0)
		unset_cmd(exec->argument);
	if (ft_strcmp(exec->argument[0], "exit") == 0)
		gb.exit_statut = exit_cmd(exec->argument);
	// else (execve(exec->argument[0], exec->argument, gb.envp) == -1)		
	// {
	// 	printf("minishell: %s: command not found\n", exec->argument[0]);
	// 	// exit(127);		
	// }
}

void	redirection(t_redircmd *redir)
{
	int fd;
	if (redir->fd == 0)
	{
		fd = open(redir->filee->content, redir->mode, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", redir->filee->content);
			exit(1);
		}
		gb.fdg =dup2(fd, 0);
		close(fd);
	}
	if (redir->fd == 1)
	{
		// if (redir->mode == 1538)
		// 	fd = open(redir->filee->content, O_RDWR |, 0644);
		// else
		fd = open(redir->filee->content, redir->mode, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", redir->filee->content);
			exit(1);
		}
		gb.fdg = dup2(fd, 1);
		close(fd);
	}
}

void executer(t_cmd *cmd)
{
	int			pipe[2];
	t_execcmd	*exec;
	t_redircmd	*redir;
	t_pipecmd	*pipecmd;

	if (cmd->type == EXEC)
	{
		exec = (t_execcmd *)(cmd);
		checifbuiltin(exec);
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redircmd *)(cmd);
		redirection(redir);
		executer(redir->cmd);
	}
	if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)(cmd);
		executer(pipecmd->left);
		executer(pipecmd->right);
	}
}