/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/19 13:56:58 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*getprompt(char **envp)
{
	return ("Minishell$ ");
}


int	main(int ac, char **argv, char **envp)
{
	char	*buffer;
	t_cmd	*cmd;
	bool	again;
	char	*ps;
	char	*es;

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
		// executer(cmd);
		print_tree(cmd);
	}
	return (0);
}