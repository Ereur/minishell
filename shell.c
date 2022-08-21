/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:09:27 by aamoussa          #+#    #+#             */
/*   Updated: 2022/08/20 19:03:55 by aamoussa         ###   ########.fr       */
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
		
		while (1)
		{
			gettoken(&buffer, &buffer[ft_strlen(buffer) - 1], &q, &eq);
			if (q == eq)
				break;
			while (q <= eq)
			{	
				printf("%c\n",*q);
				q++;
			}
		}
	}
	return (0);
}