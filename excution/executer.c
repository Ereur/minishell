/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:08:23 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/20 06:52:51 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/execution.h"
#include "../parser.h"

int	checifbuiltin(t_execcmd *exec)
{
	if (ft_strcmp(exec->argument[0], "cd") == 0)	
		cd_cmd(exec->argument);
	else if (ft_strcmp(exec->argument[0], "pwd") == 0)
		built_in_pwd(exec->argument);
	else if  (ft_strcmp(exec->argument[0], "env") == 0)	
		env();
	else if (ft_strcmp(exec->argument[0], "echo") == 0)	
		ft_echo(exec->argument);
	else if (ft_strcmp(exec->argument[0], "export") == 0)
	{		
		ft_export(exec->argument);
		get_envp();
	}
	else if (ft_strcmp(exec->argument[0], "unset") == 0)
		unset_cmd(exec->argument);
	else if (ft_strcmp(exec->argument[0], "exit") == 0)
		gb.exit_statut = exit_cmd(exec->argument);
	else
		return (1);
	return (0);
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
	// fprintf(stderr,"%s\ntest\n", cmd->argument[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	int i = 0;
	while (cmd->argument[i])
	{
		printf("test %s\n", cmd->argument[i++]);
	}
	if (execve(cmd->argument[0], cmd->argument, gb.envp) == -1)
	{
		perror("command not found");
		exit(1);
	}
}

void excute_pipes(t_cmd *cmd, int flag)
{
	int			fd[2];
	pipe(fd);
	int i;
	t_execcmd	*exec;
	t_pipecmd	*pipecmd;

	if (cmd->type == EXEC)
	{
		exec = (t_execcmd *)(cmd);
		
		if (flag == 0)
		{
			i = my_fork();
			if (i == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				if (checifbuiltin((t_execcmd *)cmd) == 0)
					execute_cmd((t_execcmd *)cmd);
				close(fd[1]);
			}
		}
		if (flag == 1)
		{
			i = my_fork();
			if (i == 0)
			{
				close(fd[1]);
				dup2(fd[0], 0);
				
				if (checifbuiltin((t_execcmd *)cmd) == 0)
					execute_cmd((t_execcmd *)cmd);
				close(fd[0]);
			}
		}
		close(fd[1]);
		close(fd[0]);
		wait(NULL);
		wait(NULL);
	}
}

void	pipe_executer(t_cmd *cmd)
{
	t_pipecmd *pipecmd;
	pipecmd = (t_pipecmd *)(cmd);
	excute_pipes(((t_pipecmd *)cmd)->left, 0);
	excute_pipes(((t_pipecmd *)cmd)->right, 1);
}

// void executer(t_cmd *cmd)
// {
// 	int			fd[2];
// 	pid_t		i;
// 	t_execcmd	*exec;
// 	t_redircmd	*redir;
// 	t_pipecmd	*pipecmd;

// 	// if (cmd->type == EXEC)
// 	// {
// 	// 	exec = (t_execcmd *)(cmd);
// 	// 	checifbuiltin(exec);
// 	// 	execute_cmd(exec);
// 	// }
// 	if (cmd->type == PIPE)
// 	{
// 		pipecmd = (t_pipecmd *)(cmd);
// 		pipe(fd);
// 		i = my_fork();
// 		if (i == 0)
// 		{	
// 			sleep(60);
// 			dup2(fd[1], 1);
// 			close(fd[1]);
// 			close(fd[0]);
// 			executer(pipecmd->left);
// 		}
// 		i = my_fork();
// 		if (i == 0)
// 		{
// 			sleep(60);
// 			dup2(fd[0], 0);
// 			close(fd[0]);
// 			close(fd[1]);
// 			executer(pipecmd->right);
// 		}
// 		// close(fd[0]);
// 		close(fd[1]);
// 	}
// }