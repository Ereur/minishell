/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:08:23 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/17 15:02:14 by zoukaddo         ###   ########.fr       */
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
	// else (execve(exec->argument[0], exec->argument, gb.envp) == -1)		
	// {
	// 	printf("minishell: %s: command not found\n", exec->argument[0]);
	// 	// exit(127);		
	// }
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
		// else
		// {
		// 	// printf("exec\n");
		// 	if (execve(exec->argument[0], exec->argument, gb.envp) == -1)
		// 	{
		// 		printf("minishell: %s: command not found\n", exec->argument[0]);
		// 		exit(127);
		// 	}
		// }
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redircmd *)(cmd);
		executer(redir->cmd);
	}
	if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)(cmd);
		executer(pipecmd->left);

		executer(pipecmd->right);
	}
	
}