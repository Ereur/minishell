/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 07:05:24 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_buffer(char **buffer)
{
	g_gb.output = dup(0);
	g_gb.status = 0;
	signals();
	ft_free(buffer);
	*buffer = readline("Minishell$ ");
	g_gb.here_doc = 0;
	if (!*buffer)
		return (0);
	if (!*buffer[0])
		return (1);
	return (2);
}

void	freee(t_cmd **cmd)
{
	if (*cmd)
	{
		free_cmd(*cmd);
		*cmd = NULL;
	}
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

void	parser_sudo(char **envp)
{
	char	*ps;
	char	*es;
	t_cmd	*cmd;
	char	*buffer;
	int		i;

	cmd = NULL;
	buffer = NULL;
	while (42)
	{
		i = get_buffer(&buffer);
		if (i == 0)
			break ;
		else if (i == 1)
			continue ;
		es = &buffer[ft_strlen(buffer)];
		add_history(buffer);
		ps = buffer;
		freee(&cmd);
		cmd = parser(&ps, es, envp);
		if (!cmd)
			continue ;
		exuctionsudo(cmd);
	}
}

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	g_gb.envp = 0;
	g_gb.input = 0;
	g_gb.output = 1;
	g_gb.fd_input_prev = 0;
	setup_env(envp);
	g_gb.curent = ft_strdup(env_grabber("PWD")->value);
	parser_sudo(envp);
	return (g_gb.exit_statut);
}
