/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:15:04 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/20 14:10:48 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *lim)
{
	int		end[2];
	char	*line;
	char	*tmp;

	pipe(end);
	line = get_next_line(0);
	lim = ft_strjoin(lim, "\n");
	if (ft_strncmp(lim, line, ft_strlen(line)))
		write(end[1], line, ft_strlen(line));
	while (ft_strncmp(lim, line, ft_strlen(line)))
	{	
		tmp = line;
		line = get_next_line(0);
		free(tmp);
		if (!ft_strncmp(lim, line, ft_strlen(line)))
			break ;
		write(1,"<",1);
		write(end[1], line, ft_strlen(line));
	}
	free(lim);
	free(line);
	dup2(end[0], 0);
	close(end[0]);
	close(end[1]);
	return (end[0]);
}
