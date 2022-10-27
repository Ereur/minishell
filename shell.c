/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/27 15:31:46 by aamoussa         ###   ########.fr       */
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

int	main(int ac, char **argv, char **envp)
{
	char	*buffer;
	t_cmd	*cmd;
	bool	again;
	char	*ps;
	char	*es;
	int		catch_last_pid;
	pid_t	pid;
	t_pipecmd *tmppipcmd;
	t_cmd *tmp;
	int npipe;
	again = true;
	g_gb.envp = 0;
	int j = 0;
	int	exit_value = 0;
	g_gb.input = 0;
	g_gb.output = 1;
	g_gb.fd_input_prev = 0;
	setup_env(envp);
	buffer = NULL;
	while (again)
	{
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
		cmd = parser(&ps, es, envp);
		if (!cmd)
			continue ;
		print_tree(cmd);
		continue ;
		// exit(1);
		// while (1)
		// 	;
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
		// print_tree(cmd);
	}
	return (0);
}
