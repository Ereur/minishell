/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:15:04 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 20:20:51 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_expand(char **line, bool i)
{
	t_list	*args;

	if (i)
	{
		args = ft_lstnew(*line, NOTHING);
		split_dollar(args, 1);
		*line = args->content;
		free(args);
	}
}

void	sig_handl(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		close(STDIN_FILENO);
		g_gb.here_doc = 1;
	}
	return ;
}

int	here_doc(char *lim, bool flag)
{
	int		end[2];
	char	*line;
	char	*tmp;

	g_gb.here_doc = 0;
	g_gb.input = dup(0);
	signal(SIGINT, sig_handl);
	pipe(end);
	line = readline("< ");
	if (g_gb.here_doc == 1)
	{
		ft_free(&line);
		close(end[1]);
		close(end[0]);
		return (-1);
	}
	if (!line)
	{	
		close(end[1]);
		return (end[0]);
	}
	here_doc_expand(&line, flag);
	if (ft_strcmp(lim, line))
		write(end[1], line, ft_strlen(line));
	while (ft_strcmp(lim, line))
	{	
		tmp = line;
		line = readline("< ");
		if (!line)
		{	
			free(tmp);
			close(end[1]);
			return (end[0]);
		}
		if (g_gb.here_doc == 1)
		{
			close(end[1]);
			close(end[0]);
			return (-1);
		}
		here_doc_expand(&line, flag);
		free(tmp);
		if (!ft_strcmp(lim, line))
			break ;
		write(end[1], line, ft_strlen(line));
	}
	free(line);
	close(end[1]);
	return (end[0]);
}
