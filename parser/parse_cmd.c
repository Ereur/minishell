/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:53:05 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/03 04:05:23 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_word(int *i, t_ends_of_tok **str, char **ps)
{

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

bool	check_quot(int *i, t_ends_of_tok **str, t_ends_of_buff *spec_ps,
					t_cmd *cmd)
{
	while (((*str)->q)[*i])
	{
		if (((*str)->q)[*i] == *(spec_ps->es))
		{
			(*i)++;
			if (!(((*str)->q)[*i]))
			{
				(*str)->eq = (*str)->q + (*i);
				*(spec_ps->ps) = (*str)->eq;
				return (true);
			}
			break ;
		}
		(*i)++;
	}
	if (!((*str)->q)[*i])
	{
		raise_error("syntax error unclosed quotes", 258, 0, cmd);
		(*str)->q = NULL;
		return (true);
	}
	return (false);
}

bool	quotes(int *i, t_ends_of_tok **str, t_ends_of_buff *spec_ps, t_cmd *cmd)
{
	if (*(spec_ps->es) != '\'' && *(spec_ps->es) != '\"')
	{
		spec_ps->es = skip_word(i, str, spec_ps->ps);
		if (!spec_ps->es)
			return (true);
		if (((*str)->q)[*i])
			(*i)++;
	}
	if (*(spec_ps->es) == '\'')
	{
		if (check_quot(i, str, spec_ps, cmd))
			return (true);
	}
	if (*(spec_ps->es) == '\"')
	{
		if (check_quot(i, str, spec_ps, cmd))
			return (true);
	}
	return (false);
}

void	quotes_pareser(t_ends_of_tok **str, char **ps, t_cmd *cmd)
{
	int				i;
	t_ends_of_buff	spec_ps;

	i = 0;
	spec_ps.ps = ps;
	if (ft_strchr((*str)->q, '\'') || ft_strchr((*str)->q, '\"'))
	{
		while (((*str)->q)[i])
		{
			spec_ps.es = &((*str)->q)[i];
			if (ft_strchr("<|> \t\r\n\v", ((*str)->q)[i]))
			{
				(*str)->eq = (*str)->q + i;
				*(spec_ps.ps) = (*str)->eq;
				return ;
			}
			i++;
			if (quotes(&i, str, &spec_ps, cmd))
				return ;
		}
		(*str)->eq = (*str)->q + i;
		*(spec_ps.ps) = (*str)->eq;
	}
}

t_cmd	*parse_exec_he(t_ends_of_tok *q_eq, t_list **args,
			t_ends_of_buff *ps_es, t_cmd *cmd)
{
	quotes_pareser(&q_eq, ps_es->ps, cmd);
	if (!q_eq->q)
		return (NULL);
	add_arg(args, &(q_eq->q), &(q_eq->eq));
	if (!parseredirec(ps_es->ps, ps_es->es, cmd))
		return (NULL);
	return (cmd);
}
