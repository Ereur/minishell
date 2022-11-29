/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:15:04 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 06:50:38 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	protect_signals(int end[2], char *line)
{
	if (g_gb.here_doc == 1)
	{
		close(end[1]);
		close(end[0]);
		return (-1);
	}
	if (!line)
	{
		close(end[1]);
		return (end[0]);
	}
	return (0);
}

int	sig_and_firstline(int *end, char *lim, bool flag)
{
	char	*line;
	char	*newline;
	int		fd;

	while (1)
	{	
		line = readline("< ");
		fd = protect_signals(end, line);
		if (fd != 0)
			return (fd);
		if (*line && ft_strcmp(lim, line))
			here_doc_expand(&line, flag);
		if (!ft_strcmp(lim, line))
			break ;
		newline = ft_strjoin(line, "\n");
		write(end[1], newline, ft_strlen(newline));
		free(newline);
		ft_free(&line);
	}
	free(line);
	close(end[1]);
	return (end[0]);
}

int	here_doc(char *lim, bool flag)
{
	int		end[2];
	int		fd;

	if (g_gb.here_doc == 1)
		return (-1);
	g_gb.input = dup(0);
	signal(SIGINT, sig_handl);
	pipe(end);
	fd = get_first_line(end, lim, flag);
	if (fd == 0)
		return (-1);
	else if (fd > 1)
		return (fd);
	return (sig_and_firstline(end, lim, flag));
}
