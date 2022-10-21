/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:15:04 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/21 07:48:10 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *lim)
{
	int		end[2];
	char	*line;
	char	*tmp;

	pipe(end);
	write(1, "<", 1);
	line = get_next_line(0);
	lim = ft_strjoin(lim, "\n");
	if (ft_strncmp(lim, line, ft_strlen(line)))
		write(end[1], line, ft_strlen(line));
	while (ft_strncmp(lim, line, ft_strlen(line)))
	{	
		tmp = line;
		write(1, "<", 1);
		line = get_next_line(0);
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
