/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/12 09:06:28 by aamoussa         ###   ########.fr       */
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
	while (again)
	{
		buffer = readline(getprompt(envp));
		if (!buffer[0])
			continue ;
		es = &buffer[ft_strlen(buffer)];
		ps = buffer;
		cmd = parsepipe(&ps, es, envp);
		nullterminating(cmd);
		print_tree(cmd);
		// while ((i = gettoken(&buffer, &buffer[ft_strlen(buffer)], &q, &eq)) && i)
		// {
		// 	printf("\ntoken type : %c\n", i);
		// 	while (q < eq)
		// 	{
		// 		printf("%c", *q);
		// 		q++;
		// 	}
		// 	printf("\n");
		// }
	}
	return (0);
}