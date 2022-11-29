/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:45:50 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 06:46:50 by aamoussa         ###   ########.fr       */
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
		g_gb.exit_statut = 1;
		g_gb.here_doc = 1;
	}
	return ;
}

int	protect_first_sig(int end[2], char *line)
{
	if (g_gb.here_doc == 1)
	{
		ft_free(&line);
		close(end[1]);
		close(end[0]);
		return (-1);
	}
	if (!line)
	{	
		g_gb.exit_statut = 0;
		close(end[1]);
		return (end[0]);
	}
	return (0);
}

int	get_first_line(int *end, char *lim, bool flag)
{
	char	*newline;
	char	*line;
	int		fd;

	line = readline("< ");
	fd = protect_first_sig(end, line);
	if (fd != 0)
		return (fd);
	if (*line && ft_strcmp(lim, line))
		here_doc_expand(&line, flag);
	if (!ft_strcmp(lim, line))
	{	
		free(line);
		return (0);
	}
	if (ft_strcmp(lim, line))
	{	
		newline = ft_strjoin(line, "\n");
		write(end[1], newline, ft_strlen(newline));
		ft_free(&newline);
		ft_free(&line);
	}
	return (-1);
}
