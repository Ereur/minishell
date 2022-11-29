/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cleanrtwo_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:34:44 by zoukado          #+#    #+#             */
/*   Updated: 2022/11/03 06:34:45 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	clen_arguments_helper(t_execcmd *execcmd, int counter)
{
	if (execcmd->args)
	{	
		make_quotes(execcmd->args, true, counter);
		if (g_gb.status)
			return (true);
		convert_list_to_args(execcmd);
	}
	return (false);
}

void	clean_arguments(t_cmd *cmd, int *counter)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		clen_arguments_helper(execcmd, *counter);
	}
	if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)(cmd);
		clean_arguments(pipecmd->left, counter);
		if (g_gb.status)
			return ;
		clean_arguments(pipecmd->right, counter);
		if (g_gb.status)
			return ;
	}
	(*counter)++;
}

void	collect_sq_and_dq(t_list **split_args, char *line, char q)
{
	char	*content;
	int		i;

	i = 0;
	while (line[i])
	{
		collect_word(split_args, line, &i, q);
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
		{
			q = line[i];
			content = ft_substr(line, i + 1, count_len(i, line, line[i]));
			ft_lstadd_back(split_args, ft_lstnew(content, q));
			i += count_len(i, line, line[i]) + 1;
		}
		if (!line[i])
			break ;
		i++;
	}
}

void	make_quotes(t_list	*args, bool i, int counter)
{
	t_list		*split_args;
	char		q;
	char		*line;
	t_list		*tmp;

	tmp = args;
	while (tmp)
	{
		split_args = NULL;
		line = tmp->content;
		if (ft_strlen(line) == 1 && line[0] == '$')
		{	
			tmp = tmp->next;
			continue ;
		}
		q = '\"';
		collect_sq_and_dq(&split_args, line, q);
		if (i)
			split_dollar(split_args, counter);
		ft_free(&tmp->content);
		tmp->content = merge_list(&split_args);
		tmp = tmp->next;
	}
}
