/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/20 03:37:53 by zoukaddo         ###   ########.fr       */
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
	pid_t	pid;
	again = true;
	gb.envp = 0;
	int j = 0;
	gb.status = 0;
	setup_env(envp);
	// env();
	while (again)
	{
		buffer = readline(getprompt(envp));
		if (!buffer[0])
			continue ;
		es = &buffer[ft_strlen(buffer)];
		add_history(buffer);
		ps = buffer;
		cmd = parser(&ps, es, envp);
		if (!cmd)
			continue;
		executer(cmd);
		// printf("exit status: %d\n", gb.exit_statut);    
		// print_tree(cmd);
	}
	return (0);
}