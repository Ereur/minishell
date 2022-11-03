/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:09:58 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/03 06:16:23 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_tok(int tok, t_cmd *cmd)
{
	if (ft_strchr(FORBIDEN_REDIR, tok))
	{	
		raise_error("syntax error near unexpected token", 258, tok, cmd);
		return (true);
	}
	return (false);
}

bool	protect_redir_input(char *file, t_execcmd *exec, char *tmp, int fd)
{	
	if (!file)
	{
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(" : ambiguous redirect\n",2);
		g_gb.exit_statut = 1;
		exec->output = -1;
		free(file);
		free(tmp);
		return (false);
	}
	else
	{
		if (fd == -1)
		{
			perror(tmp);
			g_gb.exit_statut = 1;
			exec->output = -1;
			free(file);
			free(tmp);
			return (false);
		}	
	}
	return (true);
}

bool	parse_input_redir(t_ends_of_buff *buff, t_ends_of_tok *str,
			t_execcmd *exec, t_tok_cmd *tok_cmd)
{
	char	*file;
	int		fd;
	char	*tmp;

	if (tok_cmd->tok != '<')
		return (false);
	tok_cmd->tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, tok_cmd->cmd);
	if (check_tok(tok_cmd->tok, tok_cmd->cmd))
		return (true);
	file = ft_substr((str)->q, 0, ((str)->eq - (str)->q));
	tmp = ft_strdup(file);
	here_doc_expander(&file, true);
	fd = open(file, O_RDWR, 0644);
	if (!protect_redir_input(file, exec, tmp, fd))
		return (false);
	if (exec->input != 0)
		close(exec->input);
	exec->input = fd;
	free(file);
	ft_free(&tmp);
	return (false);
}

bool	protect_output_redir(char *file, t_execcmd *exec, char *tmp, int fd)
{
	if (!file)
	{
		ft_fprintf(2, "%s : ambiguous redirect\n", tmp);
		g_gb.exit_statut = 1;
		(exec)->output = -1;
		free(file);
		free(tmp);
		return (false);
	}
	else
	{
		if (fd == -1)
		{
			perror(tmp);
			g_gb.exit_statut = 1;
			(exec)->output = -1;
			free(file);
			free(tmp);
			return (false);
		}	
	}
	return (true);
}

bool	parse_output_redir(t_ends_of_buff *buff, t_ends_of_tok *str,
		t_execcmd *exec, t_tok_cmd *tok_cmd)
{
	char	*file;
	int		fd;
	char	*tmp;

	if (tok_cmd->tok != '>')
		return (false);
	tok_cmd->tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, tok_cmd->cmd);
	if (!str->q)
		return (true);
	if (check_tok(tok_cmd->tok, tok_cmd->cmd))
		return (true);
	file = ft_substr((str)->q, 0, ((str)->eq - (str)->q));
	tmp = ft_strdup(file);
	here_doc_expander(&file, true);
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (!protect_output_redir(file, exec, tmp, fd))
		return (false);
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

	args = ft_lstnew(*here_doc_lim, NOTHING);
	make_quotes(args, i, 1);
	*here_doc_lim = args->content;
	free(args);
}

bool	parse_heredoc(t_ends_of_buff *buff, t_ends_of_tok *str,
	t_execcmd *exec, t_tok_cmd *tok_cmd)
{
	char	*here_doc_lim;
	int		her_doc_len;
	bool	flag;

	flag = true;
	if (tok_cmd->tok != '-')
		return (false);
	here_doc_lim = NULL;
	tok_cmd->tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, tok_cmd->cmd);
	if (!str->q)
		return (true);
	if (check_tok(tok_cmd->tok, tok_cmd->cmd))
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

bool	output_append_protection(char *file, t_execcmd *exec, char *tmp, int fd)
{
	if (!file)
	{
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(" : ambiguous redirect\n", 2);
		g_gb.exit_statut = 1;
		(exec)->output = -1;
		free(file);
		free(tmp);
		return (false);
	}
	else
	{
		if (fd == -1)
		{
			perror(tmp);
			g_gb.exit_statut = 1;
			(exec)->output = -1;
			free(file);
			free(tmp);
			return (false);
		}	
	}
	return (true);
}

bool	parse_output_append(t_ends_of_buff *buff, t_ends_of_tok *str,
				t_execcmd *exec, t_tok_cmd *tok_cmd)
{
	char	*file;
	int		fd;
	char	*tmp;

	if (tok_cmd->tok != '+')
		return (false);
	tok_cmd->tok = gettoken(buff->ps, buff->es, &(str)->q, &(str)->eq);
	quotes_pareser(&str, buff->ps, tok_cmd->cmd);
	if (!str->q)
		return (true);
	if (check_tok(tok_cmd->tok, tok_cmd->cmd))
		return (true);
	file = ft_substr((str)->q, 0, ((str)->eq - (str)->q));
	tmp = ft_strdup(file);
	here_doc_expander(&file, true);
	fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (!output_append_protection(file, exec, tmp, fd))
		return (false);
	if (exec->output != 1)
		close(exec->output);
	exec->output = fd;
	free(file);
	free(tmp);
	return (false);
}

t_cmd	*parseredirec(char **ps, char *es, t_cmd *cmd)
{
	t_ends_of_tok	q_and_eq;
	t_ends_of_buff	buff;
	t_execcmd		*exec;
	t_tok_cmd		tok_cmd;

	buff.ps = (ps);
	buff.es = es;
	exec = (t_execcmd *)cmd;
	tok_cmd.cmd = cmd;
	while (skip_and_find(buff.ps, buff.es, "<>"))
	{
		tok_cmd.tok = gettoken(buff.ps, buff.es, 0, 0);
		if (parse_input_redir(&buff, &q_and_eq, exec, &tok_cmd))
			return (NULL);
		if (parse_output_redir(&(buff), &(q_and_eq), exec, &tok_cmd))
			return (NULL);
		if (parse_heredoc(&buff, &q_and_eq, exec, &tok_cmd))
			return (NULL);
		if (parse_output_append(&buff, &q_and_eq, exec, &tok_cmd))
			return (NULL);
	}
	return ((t_cmd *)(exec));
}
