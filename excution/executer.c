/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:08:23 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/22 19:10:15 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/execution.h"
#include "../parser.h"

int	checifbuiltin(t_execcmd *exec)
{
	if (ft_strcmp(exec->argument[0], "cd") == 0)
	{		
		cd_cmd(exec->argument);
		return (0);
	}
	if (ft_strcmp(exec->argument[0], "pwd") == 0)
	{		
		built_in_pwd(exec->argument);
		return (0);
	}
	if (ft_strcmp(exec->argument[0], "env") == 0)
	{		
		env();
		return (0);
	}
	if (ft_strcmp(exec->argument[0], "echo") == 0)
	{		
		ft_echo(exec->argument);
		return (0);
	}
	if (ft_strcmp(exec->argument[0], "export") == 0)
	{		
		ft_export(exec->argument);
		return (0);
	}
	if (ft_strcmp(exec->argument[0], "unset") == 0)
	{	
		unset_cmd(exec->argument);
		return (0);
	}
	if (ft_strcmp(exec->argument[0], "exit") == 0)
	{	
		gb.exit_statut = exit_cmd(exec->argument);
		return (0);
	}
	return (1);
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
		dup2(fd, 0);
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
		dup2(fd, 1);
		close(fd);
	}
}

char **get_paths(void)
{
	int		i;
	t_senv	*tmp;
	char	**paths;

	i = 0;
	tmp = gb.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
		{	
			paths = ft_split(tmp->value, ':');
			if (paths)
			{
				while (paths[i])
				{
					paths[i] = ft_strjoin(paths[i], "/");
					i++;
				}
				return (paths);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	check_access(char **paths, t_execcmd *cmd)
{
	int		i;
	char	*tmp;
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd->argument[0]);
		// write(2,"tmp", ft_strlen(tmp));
		// write(2,"\n", 1);
		if (!access(tmp, X_OK))
		{
			cmd->argument[0] = tmp;
			// fprintf(stderr, "%s\n", cmd->argument[0]);
			return ;
		}
		i++;
	}
}

void	execute_cmd(t_execcmd *cmd)
{
	char	**paths;

	paths = get_paths();
	check_access(paths, cmd);
	// fprintf(2,"paths");
	if (execve(cmd->argument[0], cmd->argument, gb.envp) == -1)
	{
		perror("execve failed");
		exit(1);
	}
}


void executer(t_cmd *cmd)
{
	int			fd[2];
	pid_t		i;
	t_execcmd	*exec;
	t_redircmd	*redir;
	t_pipecmd	*pipecmd;

	if (cmd->type == EXEC)
	{
		exec = (t_execcmd *)(cmd);
		checifbuiltin(exec);
		execute_cmd(exec);
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
		pipe(fd);
		i = my_fork();
		if (i == 0)
		{	
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			executer(pipecmd->left);
		}
		i = my_fork();
		if (i == 0)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			executer(pipecmd->right);
		}
		// close(fd[0]);
		close(fd[1]);
	}
}