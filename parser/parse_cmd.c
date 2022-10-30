/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:53:05 by aamoussa          #+#    #+#             */
/*   Updated: 2022/10/30 07:16:40 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_word(int *i, t_ends_of_tok **str, char **ps)
{
	char	*tmp;
	int		check;

	while (((*str)->q)[*i])
	{
		if (((*str)->q)[*i] == '\'' || ((*str)->q)[*i] == '\"')
			break ;
		if (ft_strchr("<|> \t\r\n\v", ((*str)->q)[*i]))
		{
			(*str)->eq = (*str)->q + (*i);
			*ps = (*str)->eq;
			return (NULL);
		}
		(*i)++;
	}
	return (&(((*str)->q)[*i]));
}

bool	check_quot(int *i, char *spec, t_ends_of_tok **str, char **ps)
{
	while (((*str)->q)[*i])
	{
		if (((*str)->q)[*i] == *spec)
		{
			(*i)++;
			if (!(((*str)->q)[*i]))
			{
				(*str)->eq = (*str)->q + (*i);
				*ps = (*str)->eq;
				return (true);
			}
			break ;
		}
		(*i)++;
	}
	if (!((*str)->q)[*i])
	{
		raise_error("syntax error unclosed quotes", 258, 0);	
		(*str)->q = NULL;
		return (true);
	}
	return (false);
}

bool	quotes(int *i, char *spec, t_ends_of_tok **str, char **ps)
{
	if (*spec != '\'' && *spec != '\"')
	{
		spec = skip_word(i, str, ps);
		if (!spec)
			return (true);
		if (((*str)->q)[*i])
			(*i)++;
	}
	if (*spec == '\'')
	{
		if (check_quot(i, spec, str, ps))
			return (true);
	}
	if (*spec == '\"')
	{
		if (check_quot(i, spec, str, ps))
			return (true);
	}
	return (false);
}

void	quotes_pareser(t_ends_of_tok **str, char **ps)
{
	char	*spec;
	int		i;

	i = 0;
	if (ft_strchr((*str)->q, '\'') || ft_strchr((*str)->q, '\"'))
	{
		while (((*str)->q)[i])
		{
			spec = &((*str)->q)[i];
			if (ft_strchr("<|> \t\r\n\v", ((*str)->q)[i]))
			{
				(*str)->eq = (*str)->q + i;
				*ps = (*str)->eq;
				return ;
			}
			i++;
			if (quotes(&i, spec, str, ps))
				return ;
		}
		(*str)->eq = (*str)->q + i;
		*ps = (*str)->eq;
	}
}

t_cmd	*parse_exec_he(t_ends_of_tok *q_eq, char **ps, t_list **args, char *es, t_cmd *cmd)
{
	quotes_pareser(&q_eq, ps);
	if (!q_eq->q)
		return (NULL);
	add_arg(args, &(q_eq->q), &(q_eq->eq));
	if (!parseredirec(ps, es, cmd))
		return (NULL);
	return (cmd);
}