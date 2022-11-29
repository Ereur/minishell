/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:06:38 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/03 07:43:53 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_exec_helper(char **ps, char *es, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (skip_and_find(ps, es, "|"))
	{
		while ((*ps + 1)[i] && ft_strchr(WHITESPACE, (*ps + 1)[i]))
			i++;
		if (!(*ps + 1)[i])
		{	
			raise_error("syntax error near unexpected token", 258, '|', cmd);
			return (true);
		}
	}
	return (false);
}

bool	prse_exec(t_ends_of_tok *q_eq, t_ends_of_buff *ps_es,
			t_execcmd *ret, t_cmd *cmd)
{
	int	tok;

	while (!skip_and_find(ps_es->ps, ps_es->es, "|"))
	{
		tok = gettoken(ps_es->ps, ps_es->es, &q_eq->q, &q_eq->eq);
		if (!tok)
			break ;
		if (!parse_exec_he(q_eq, &ret->args, ps_es, cmd))
			return (false);
	}
	return (true);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd			*cmd;
	t_execcmd		*ret;
	t_ends_of_tok	q_eq;
	t_ends_of_buff	ps_es;

	cmd = execcmd();
	ps_es.ps = ps;
	ps_es.es = es;
	ret = (t_execcmd *)(cmd);
	ret->args = NULL;
	if (skip_and_find(ps_es.ps, ps_es.es, "|"))
	{	
		raise_error("syntax error near unexpected token", 258, '|', cmd);
		return (NULL);
	}
	cmd = parseredirec(ps_es.ps, ps_es.es, cmd);
	if (!cmd)
		return (NULL);
	if (!prse_exec(&q_eq, &ps_es, ret, cmd))
		return (NULL);
	if (parse_exec_helper(ps_es.ps, ps_es.es, cmd))
		return (NULL);
	return (cmd);
}

t_cmd	*parsepipe(char **ps, char *es, char **envp)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = parseexec(ps, es);
	if (!cmd)
		return (NULL);
	if (skip_and_find(ps, es, "|"))
	{	
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es, envp));
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_cmd	*parser(char **ps, char *es, char **envp)
{
	t_cmd	*cmd;
	char	*s;
	int		counter;

	counter = 0;
	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (s >= es)
		return (NULL);
	cmd = parsepipe(ps, es, envp);
	clean_arguments(cmd, &counter);
	if (g_gb.status)
		return (NULL);
	return (cmd);
}
