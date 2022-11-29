/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:31:08 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 07:31:20 by aamoussa         ###   ########.fr       */
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
	if (!*file)
	{
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(" : ambiguous redirect\n", 2);
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
	if (!*file)
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
