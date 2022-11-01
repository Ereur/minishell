/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:09:58 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/01 13:54:36 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_input_redir(t_ends_of_buff *buff, t_ends_of_tok *str,
		t_execcmd *exec, int tok, t_cmd *cmd)
{
	char	*file;
	int		fd;
	char	*tmp;

	if (tok != '<')
		return (false);
	tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, cmd);
	if (ft_strchr(FORBIDEN_REDIR, tok))
	{	
		raise_error("syntax error near unexpected token", 258, tok, cmd);
		return (true);
	}
	file = ft_substr((str)->q, 0, ((str)->eq - (str)->q));
	here_doc_expander(&file, true);
	tmp = ft_strdup(file);
	if (!*file)
	{
		printf("%s : ambiguous redirect\n", tmp);
		g_gb.exit_statut = 1;
		exec->output = -1;
		free(file);
		free(tmp);
		return (false);
	}
	else
	{
		fd = open(file, O_RDWR, 0644);
		if (fd == -1)
		{
			g_gb.exit_statut = 1;
			g_gb.status = 1;
			perror(tmp);
		}	
	}
	if (exec->input != 0)
		close(exec->input);
	exec->input = fd;
	free(file);
	ft_free(&tmp);
	return (false);
}

bool	parse_output_redir(t_ends_of_buff *buff, t_ends_of_tok *str,
		t_execcmd *exec, int tok, t_cmd *cmd)
{
	char	*file;
	int		fd;
	char	*tmp;

	if (tok != '>')
		return (false);
	tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, cmd);
	if (!str->q)
		return (true);
	if (ft_strchr(FORBIDEN_REDIR, tok))
	{	
		raise_error("syntax error near unexpected token", 258, tok, cmd);
		return (true);
	}
	file = ft_substr((str)->q, 0, ((str)->eq - (str)->q));
	tmp = ft_strdup(file);
	here_doc_expander(&file, true);
	if (!*file)
	{
		printf("%s : ambiguous redirect\n", tmp);
		g_gb.exit_statut = 1;
		exec->output = -1;
		free(file);
		free(tmp);
		return (false);
	}
	else
	{
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
		{
			g_gb.exit_statut = 1;
			g_gb.status = 1;
			perror(tmp);
		}	
	}
	if (exec->output != 1)
		close(exec->output);
	exec->output = fd;
	free(file);
	free(tmp);
	return (false);
}

void	here_doc_expander(char **here_doc_lim, bool i)
{
	t_list	*args;
	// char	*tmp;

	args = ft_lstnew(*here_doc_lim, NOTHING);
	make_quotes(args, i, 1);
	*here_doc_lim = args->content;
	free(args);
}

bool	check_tok(int tok, t_cmd *cmd)
{
	if (ft_strchr(FORBIDEN_REDIR, tok))
	{	
		raise_error("syntax error near unexpected token", 258, tok, cmd);
		return (true);
	}
	return (false);
}

bool	parse_heredoc(t_ends_of_buff *buff, t_ends_of_tok *str,
		t_execcmd *exec, int tok, t_cmd *cmd)
{
	char	*here_doc_lim;
	int		her_doc_len;
	bool	flag;

	flag = true;
	if (tok != '-')
		return (false);
	here_doc_lim = NULL;
	tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, cmd);
	if (!str->q)
		return (true);
	if (check_tok(tok, cmd))
		return (true);
	her_doc_len = ((str)->eq - (str)->q);
	here_doc_lim = ft_substr((str)->q, 0, her_doc_len);
	if (ft_strchr(here_doc_lim, '\"') || ft_strchr(here_doc_lim, '\''))
		flag = false;
	here_doc_expander(&here_doc_lim, false);
	exec->input = here_doc(here_doc_lim, flag);
	dup2(g_gb.input, 0);
	signals();
	ft_free(&here_doc_lim);
	return (false);
}

bool	parse_output_append(t_ends_of_buff *buff, t_ends_of_tok *str,
		t_execcmd *exec, int tok, t_cmd *cmd)
{
	char	*file;
	int		fd;
	char	*tmp;

	if (tok != '+')
		return (false);
	tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, cmd);
	if (!str->q)
		return (true);
	if (ft_strchr(FORBIDEN_REDIR, tok))
	{	
		raise_error("syntax error near unexpected token", 1, tok, cmd);
		return (true);
	}
	file = ft_substr((str)->q, 0, ((str)->eq - (str)->q));
	tmp = ft_strdup(file);
	here_doc_expander(&file, true);
	if (!*file)
	{
		printf("%s : ambiguous redirect\n", tmp);
		g_gb.exit_statut = 1;
		exec->output = -1;
		free(file);
		free(tmp);
		return (false);
	}
	else
	{
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
		{
			g_gb.exit_statut = 1;
			perror(tmp);
		}	
	}
	if (exec->output != 1)
		close(exec->output);
	exec->output = fd;
	free(file);
	free(tmp);
	return (false);
}

t_cmd	*parseredirec(char **ps, char *es, t_cmd *cmd)
{
	int				tok;
	t_ends_of_tok	q_and_eq;
	t_ends_of_buff	buff;
	t_execcmd		*exec;

	buff.ps = (ps);
	buff.es = es;
	exec = (t_execcmd *)cmd;
	while (skip_and_find(buff.ps, buff.es, "<>"))
	{
		tok = gettoken(buff.ps, buff.es, 0, 0);
		if (parse_input_redir(&buff, &q_and_eq, exec, tok, cmd))
			return (NULL);
		if (parse_output_redir(&buff, &q_and_eq, exec, tok, cmd))
			return (NULL);
		if (parse_heredoc(&buff, &q_and_eq, exec, tok, cmd))
			return (NULL);
		if (parse_output_append(&buff, &q_and_eq, exec, tok, cmd))
			return (NULL);
	}
	return ((t_cmd *)(exec));
}