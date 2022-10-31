/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:15:04 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 14:13:04 by aamoussa         ###   ########.fr       */
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
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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
	signal(SIGINT, sig_handl);
	pipe(end);
	write(1, "< ", 2);
	line = get_next_line(0);
	if (!line)
	{	
		close(end[1]);
		return (end[0]);
	}
	if (g_gb.here_doc == 1)
	{
		// ft_free(&lim);
		ft_free(&line);
		close(end[1]);
		close(end[0]);
		return (-1);
	}
	lim = ft_strjoin(lim, "\n");
	here_doc_expand(&line, flag);
	if (ft_strncmp(lim, line, ft_strlen(line)))
		write(end[1], line, ft_strlen(line));
	while (ft_strncmp(lim, line, ft_strlen(line)))
	{	
		tmp = line;
		write(1, "< ", 2);
		line = get_next_line(0);
		if (!line)
		{	
			free(line);
			free(lim);
			free(tmp);
			close(end[1]);
			return (end[0]);
		}
		if (g_gb.here_doc == 1)
		{
			ft_free(&lim);
			ft_free(&line);
			close(end[1]);
			close(end[0]);
			return (-1);
		}
		here_doc_expand(&line, flag);
		free(tmp);
		if (!ft_strncmp(lim, line, ft_strlen(line)))
			break ;
		write(end[1], line, ft_strlen(line));
	}
	free(lim);
	free(line);
	close(end[1]);
	return (end[0]);
}
