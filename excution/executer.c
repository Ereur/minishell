/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:08:23 by zoukaddo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/20 06:52:51 by aamoussa         ###   ########.fr       */
=======
/*   Updated: 2022/10/20 07:50:28 by zoukaddo         ###   ########.fr       */
>>>>>>> ad332cbd8b7fdfd6694de3d0117d7359ec30b0c7
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
	else if (ft_strcmp(exec->argument[0], "env") == 0)	
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
}

void	redirection(t_redircmd *redir)
{
	int	fd;

	if (redir->fd == 0)
	{
		fd = open(redir->filee->content, redir->mode, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", \
				redir->filee->content);
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (redir->fd == 1)
	{
		fd = open(redir->filee->content, redir->mode, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", \
				redir->filee->content);
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
	}
}

char	**get_paths(void)
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
		if (!access(tmp, X_OK))
		{
			cmd->argument[0] = tmp;
			return ;
		}
		i++;
	}
}

void	error_display(char *message, char *cmd, int fd)
{
	if (cmd)
	{
		if (ft_strchr(cmd, '/'))
		{
			write(fd, "no such file or directory : ", 28);
			write(fd, cmd, ft_strlen(cmd));
			write(fd, "\n", 1);
			exit(1);
		}
		write(fd, message, ft_strlen(message));
		write(fd, cmd, ft_strlen(cmd));
		write(fd, "\n", 1);
		exit(1);
	}
	else
	{
		write(fd, message, ft_strlen(message));
		exit(1);
	}
}

void	execute_cmd(t_execcmd *cmd)
{
	char	**paths;

	paths = get_paths();
	check_access(paths, cmd);
<<<<<<< HEAD
	// fprintf(stderr,"%s\ntest\n", cmd->argument[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	int i = 0;
	while (cmd->argument[i])
	{
		printf("test %s\n", cmd->argument[i++]);
	}
=======
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
>>>>>>> ad332cbd8b7fdfd6694de3d0117d7359ec30b0c7
	if (execve(cmd->argument[0], cmd->argument, gb.envp) == -1)
	{
		perror("");
		// error_display("command not found: ", cmd->argument[0], 2);
		exit(1);
	}
}

void	excute_pipes(t_cmd *cmd, int flag)
{
	int			fd[2];
	int			i;
	t_execcmd	*exec;
	t_pipecmd	*pipecmd;

	pipe(fd);
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
		close(fd[1]);
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

void	exec_command(t_cmd *first_cmd, t_execcmd *cmd, int npipe, int cpipe)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = my_fork();
	if (!pid)
	{
		// printf("%d pid\n",pid);
		if (cmd->input < 0 || cmd->output < 0)
			exit(69);
		if (cmd->input != 0)
			dup2(cmd->input, 0);
		else
			dup2(gb.fd_input_prev, 0);
		if (cmd->output != 1)
			dup2(cmd->output, 1);
		else if (cpipe < npipe)
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
		exit(1);
	}
	close(fd[1]);
	if (gb.fd_input_prev != 0)
		close(gb.fd_input_prev);
	gb.fd_input_prev = fd[0];
	return ;
}

void	pipe_executer(t_cmd *first_cmd, t_cmd *cmd, int npipe, int cpipe)
{
	t_pipecmd	*pipecmd;
	int			i;

	i = 0;
	pipecmd = (t_pipecmd *)(cmd);
	if (!cmd)
		return ;
	if (cmd->type == PIPE)
	{
		pipe_executer(first_cmd, pipecmd->left, npipe, cpipe);
		pipe_executer(first_cmd, pipecmd->right, npipe, cpipe + 1);
	}
	exec_command(first_cmd, (t_execcmd *)cmd, npipe, cpipe);
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