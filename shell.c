/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by aamoussa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/16 16:39:32 by zoukaddo         ###   ########.fr       */
=======
/*   Updated: 2022/09/16 16:18:01 by aamoussa         ###   ########.fr       */
>>>>>>> c6c1840004ea643bb4d1d128133d08be6f27a232
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
<<<<<<< HEAD
	gb.envp = 0;
	int j = 0;
	setup_env(envp);
	env();
	exit(1);
=======
	variable.envp = envp;
	variable.status = 0;	
>>>>>>> c6c1840004ea643bb4d1d128133d08be6f27a232
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
		print_tree(cmd);
	}
	return (0);
}