/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:06:38 by aamoussa          #+#    #+#             */
/*   Updated: 2022/08/25 07:33:58 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void double_quote_parser(char **q, char **eq)
{
	if (skip_and_find(q, *eq, "\""))
	{
		
	}
}

void nullterminating(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_redircmd	*redir;
	t_pipecmd	*pipecmd;
	int			i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)(cmd);
		while (execcmd->eargv[i])
			*execcmd->eargv[i++] = 0;
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redircmd *)cmd;
		*redir->efile = 0;
		nullterminating(redir->cmd);
	}
	if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)(cmd);
		nullterminating(pipecmd->left);
		nullterminating(pipecmd->right);
	}
}

void ft_print_som(char *q, char *eq)
{
	while (q < eq)
	{	
		printf("%c", *q);
		q++;
	}
	printf("\n");

}

// void print_helper();
void print_tree(t_cmd *cmd)
{
	t_execcmd *execcm;
	t_redircmd *redir;
	t_pipecmd	*pipe;
	int i;
	i = 0;
	// if (!cmd)
	// 	return ;
	if (cmd->type == REDIR)
	{
			redir = (t_redircmd *)(cmd);
			printf("\n----------redirection-------\n");
			// ft_print_som(redir->file, redir->efile);
			printf("%s\n", redir->file);
			printf("fd %d\n", redir->fd);
			printf(" \nmode %d\n", redir->mode);
			print_tree(redir->cmd);
	}
	if (cmd->type == EXEC)
	{
		execcm = (t_execcmd	*)(cmd);
		printf("\n----------Arguments-------\n");
		while (execcm->argv[i])
		{	
			ft_print_som(execcm->argv[i], execcm->eargv[i]);
			i++;
		}		
	}
	if (cmd->type == PIPE)
	{
		pipe = (t_pipecmd *)(cmd);
		printf("\nPIPE\n");
		print_tree(pipe->left);
		print_tree(pipe->right);
	}
}

t_cmd *parseredirec(char **ps, char *es, t_cmd *cmd)
{
	int		tok;
	char	*q;
	char	*eq;
	// t_cmd		*cmd;
	
	while (skip_and_find(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (tok == '<')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
				raise_error("syntax error near unexpected token", 1, tok);
			cmd = redirecmd(cmd, q, eq, O_RDONLY, 0);
		}
		else if ('>')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
				raise_error("syntax error near unexpected token", 1, tok);
			cmd = redirecmd(cmd, q, eq, O_RDWR|O_TRUNC|O_CREAT, 1);
		}
		else if ('-')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
				raise_error("syntax error near unexpected token", 1, tok);
			cmd = redirecmd(cmd, q, eq, O_RDONLY, 0);
		}
		else if ('+')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
				raise_error("syntax error near unexpected token", 1, tok);
			cmd = redirecmd(cmd, q,eq, O_RDWR|O_CREAT, 1);
		}
	}
	return (t_cmd *)(cmd);
}

t_cmd *parseexec(char **ps, char *es)
{
	t_cmd		*cmd;
	t_execcmd	*ret;
	char		*q;
	char		*eq;
	int			tok;
	int			argc;

	argc = 0;
	cmd = execcmd();
	ret = (t_execcmd *)(cmd);
	cmd = parseredirec(ps, es, cmd);
	if (skip_and_find(ps,es, "|"))
			raise_error("syntax error near unexpected token", 1, '|');
	if(skip_and_find_0(ps, es))
			raise_error("syntax error near unexpected token", 1, '|');
	while (!skip_and_find(ps , es, "|"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (!tok)
			break;
		// skip_and_find_quotes(ps, );
		if (tok != 'a')
		{
			printf("syntax error");
			exit(1);
		}
		double_quote_parser(&q, &eq);
		ret->argv[argc] = q;
		ret->eargv[argc] = eq;
		argc++;
		cmd = parseredirec(ps ,es, cmd);
	}
	ret->argv[argc] = 0;
	ret->eargv[argc] = 0;
	return (cmd);
}

t_cmd *parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;
	cmd = NULL;
	cmd = parseexec(ps, es);
	if (skip_and_find(ps , es, "|"))
	{	
		gettoken(ps , es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
		// printf("hehe%d\n", cmd->type);
	}
	return (cmd);
}


