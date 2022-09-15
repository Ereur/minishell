/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/15 17:43:29 by aamoussa         ###   ########.fr       */
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
	t_cmd *cmd;
	bool	again;
	char	*ps;
	char	*es;
	char	*q;
	char	*eq;
	int		i;

	q = NULL;
	eq = NULL;
	again = true;
	variable.envp = envp;
	int j = 0;
	while (variable.envp[j++])
		ft_lstadd_back(&variable.env, ft_lstnew(variable.envp[j], NOTHING));

	while (again)
	{
		buffer = readline(getprompt(envp));
		if (!buffer[0])
			continue ;
		es = &buffer[ft_strlen(buffer)];
		add_history(buffer);
		ps = buffer;
		cmd = parsepipe(&ps, es, envp);
		nullterminating(cmd);
		// exit(1);
		clean_arguments(cmd);
		print_tree(cmd);
	}
	return (0);
}