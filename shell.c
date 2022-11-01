/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/01 11:53:25 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*getprompt(char **envp)
{
	return ("Minishell$ ");
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork process");
		exit(1);
	}
	return (pid);
}

void	exuctionsudo(t_cmd *cmd)
{
	int			npipe;
	t_cmd		*tmp;
	t_pipecmd	*tmppipcmd;

	get_envp();
	if (cmd->type == EXEC)
		execute_builtins(cmd);
	else
	{
		npipe = 0;
		tmp = cmd;
		while (tmp->type == PIPE)
		{
			tmppipcmd = (t_pipecmd *)(tmp);
			tmp = tmppipcmd->right;
			npipe++;
		}
		pipe_executer(cmd, cmd, npipe, 0);
		close_all_fds(cmd);
		close(g_gb.fd_input_prev);
		g_gb.fd_input_prev = 0;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitforcprocess();
	}
}

void	free_args_list(t_list **args)
{
	while ((*args))
	{
		ft_free(&((*args)->content));
		(*args) = (*args)->next;
	}
}

void	free_all(t_cmd *cmd)
{
	t_pipecmd	*pipcmd;
	t_execcmd	*execcmd;
	int			i;

	i = 0;
	if (cmd->type == PIPE)
	{
		pipcmd = (t_pipecmd *)(cmd);
		free_all(pipcmd->left);
		free_all(pipcmd->right);
		free(pipcmd);
	}
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)(cmd);
		while (execcmd->argument && execcmd->argument[i])
			ft_free(&execcmd->argument[i++]);
		free_args_list(&(execcmd->args));
		free(execcmd->argument);
		free(execcmd);
	}
}

void	free_cmd(t_cmd *cmd)
{
	free_all(cmd);
}

void	parser_sudo(char **envp)
{
	char	*buffer;
	char	*ps;
	char	*es;
	t_cmd	*cmd;

	buffer = NULL;
	cmd = NULL;
	while (42)
	{
		g_gb.output = dup(0);
		g_gb.status = 0;
		signals();
		ft_free(&buffer);
		buffer = readline(getprompt(envp));
		if (!buffer)
			break ;
		if (!buffer[0])
			continue ;
		es = &buffer[ft_strlen(buffer)];
		add_history(buffer);
		ps = buffer;
		if (cmd)
		{
			free_cmd(cmd);
			cmd = NULL;
		}
		cmd = parser(&ps, es, envp);
		if (!cmd)
			continue ;
		exuctionsudo(cmd);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_cmd	*cmd;

	g_gb.envp = 0;
	g_gb.input = 0;
	g_gb.output = 1;
	g_gb.fd_input_prev = 0;
	setup_env(envp);
	g_gb.curent = ft_strdup(env_grabber("PWD")->value);
	parser_sudo(envp);
	return (0);
}
