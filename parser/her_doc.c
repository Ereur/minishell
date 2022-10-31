/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:15:04 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/30 14:20:07 by aamoussa         ###   ########.fr       */
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

int	here_doc(char *lim, bool flag)
{
	int		end[2];
	char	*line;
	char	*tmp;

	pipe(end);
	write(1, "< ", 2);
	line = get_next_line(0);
	if (!line)
	{	
		close(end[1]);
		return (end[0]);
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
			free(lim);
			free(tmp);
			close(end[1]);
			return (end[0]);
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
