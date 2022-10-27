/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:06:38 by aamoussa          #+#    #+#             */
/*   Updated: 2022/10/27 15:54:26 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

int find_name(char *s)
{
	char *tmp;
	char *name;
	int  i;

	i = 0;
	tmp = s;
	name = NULL;
	if (*tmp == '?')
		return (1);
	while (*tmp)
	{
		if (!ft_isalpha(*tmp) && *tmp!='_')
			break;
		tmp++;
		i++;
	}
	return (i);
}

int skip_dollar(char *str) 
{
	int i;
	
	i = 0;
	str = ft_strchr(str, '$');
	while (str && *str == '$')
	{
		str++;	
		i++;
	}
	return (i);
}

void put_zero_in_null(char **str)
{
	char *tmp;

	tmp = NULL;
	tmp = *str;
	if (!tmp)
	{
		tmp = (char *)malloc(1);
		tmp[0] = 0;
	}
	*str = tmp;
}

char *join(char *str, size_t i, char *name, char *ret)
{
	char *result;
	char *dest;

	result = NULL;
	if (i > 0)
	{	
		dest = (char *)malloc(i);
		result =  ft_strncpy(dest, str, i);	
	}
	put_zero_in_null(&name);
	put_zero_in_null(&ret);
	put_zero_in_null(&result);
	result = ft_strjoin(result, name);
	result = ft_strjoin(ret, result);
	return (result);
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

void print_tree(t_cmd *cmd)
{
	t_execcmd *execcm;
	t_redircmd *redir;
	t_pipecmd	*pipe;

	int i;
	i = 0;
	// if (!cmd)
	// 	return ;
	// if (cmd->type == REDIR)
	// {
	// 		redir = (t_redircmd *)(cmd);
	// 		printf("\n----------redirection-------\n");
	// 		// ft_print_som(redir->file, redir->efile);
	// 		printf("|%s|\n", redir->filee->content);
	// 		printf("fd %d\n", redir->fd);
	// 		printf(" \nmode %d\n", redir->mode);
	// 		print_tree(redir->cmd);
	// }
	if (cmd->type == EXEC)
	{
		int	i;

		i = 0;
		execcm = (t_execcmd	*)(cmd);
		t_list *tmp;

		tmp = execcm->args;
		printf("\n----------Arguments-------\n");
		// while (tmp)
		// {	
		// 	// ft_print_som(execcm->argv[i], execcm->eargv[i]);
		// 	// write(1,&execcm->argv[i], ft_strlen(execcm->argv[i]));
		// 	printf("|%s|\n", tmp->content);
		// 	tmp = tmp->next;
		// }
		while (execcm->argument && execcm->argument[i])
		{
			printf("|%s|\n",execcm->argument[i]);
			i++;
		}
		printf("output : %d \n input : %d \n", execcm->output, execcm->input);
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
	char	*here_doc_lim;
	int		her_doc_len;
	int		fd;
	t_execcmd	*exec;
	char	*file;

	exec = (t_execcmd *)cmd;
	here_doc_lim = NULL;
	her_doc_len = 0;
	// t_cmd		*cmd;

	while (skip_and_find(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (tok == '<')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
			{	
				raise_error("syntax error near unexpected token", 258, tok);
				return (NULL);
			}
			file = ft_substr(q, 0, (eq - q));
			fd = open(file, O_RDWR, 0644);
			if (fd == -1)
			{
				printf("%s : No such file or directory\n", file);
			}
			if (exec->input != 0)
				close(exec->input);
			exec->input = fd;
			free(file);
			// cmd = redirecmd(cmd, q, eq, O_RDONLY, 0);
		}
		else if (tok == '>')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
			{	
				raise_error("syntax error near unexpected token", 258, tok);
				return (NULL);
			}
			file = ft_substr(q, 0, (eq - q));
			fd = open(file, O_RDWR|O_TRUNC|O_CREAT, 0644);
			if (fd == -1)
			{
				printf("%s : No such file or directory\n", file);
			}
			if (exec->output != 1)
				close(exec->output);
			exec->output = fd;
			free(file);
			// cmd = redirecmd(cmd, q, eq, O_RDWR|O_TRUNC|O_CREAT, 1);
		}
		else if (tok == '-')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
			{	
				raise_error("syntax error near unexpected token", 258, tok);
				return (NULL);
			}
			her_doc_len = (eq - q);
			here_doc_lim = ft_substr(q, 0, her_doc_len);
			exec->input = here_doc(here_doc_lim);
			ft_free(&here_doc_lim);
			// cmd = redirecmd(cmd, q, eq, O_RDONLY, 0);
		}
		else if (tok == '+')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
			{	
				raise_error("syntax error near unexpected token", 1, tok);
				return (NULL);
			}
			file = ft_substr(q, 0, (eq - q));
			fd = open(file, O_RDWR|O_APPEND|O_CREAT, 0644);
			if (fd == -1)
			{
				printf("%s No such file or directory\n", file);
			}
			if (exec->output !=  1)
				close(exec->output);
			exec->output = fd;
			free(file);
			// cmd = redirecmd(cmd, q,eq, O_RDWR|O_APPEND|O_CREAT, 1);
		}
	}
	return (t_cmd *)(exec);
}

char *skip_word(int *i, t_ends_of_tok **str, char **ps)
{
	char	*tmp;
	int		check;

	while ((*q)[*i])
	{
		if ((*q)[*i] == '\'' || (*q)[*i] == '\"')
			break ;
		if (ft_strchr("<|> \t\r\n\v", (*q)[*i]))
		{
			*eq = *q + (*i);
			*ps = *eq;
			return (NULL);
		}
		(*i)++;
	}
	return (&(*q)[*i]);
}

// char *skip_word(int *i, char **q, char **eq, char **ps)
// {
// 	char	*tmp;
// 	char	*str;
// 	int		check;
//
// 	str = "<|> \t\r\n\v";
// 	while ((*q)[*i])
// 	{
// 		if ((*q)[*i] == '\'' || (*q)[*i] == '\"')
// 			break ;
// 		if (ft_strchr("<|> \t\r\n\v", (*q)[*i]))
// 		{
// 			*eq = *q + (*i);
// 			*ps = *eq;
// 			return (NULL);
// 		}
// 		(*i)++;
// 	}
// 	return (&(*q)[*i]);
// }

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

void	quotes_pareser(t_ends_of_tok **str, char **ps)
{
	char	*single_quotes;
	char	*double_quotes;
	char	*spec;
	int		i;

	i = 0;
	single_quotes = ft_strchr((*str)->q, '\'');
	double_quotes = ft_strchr((*str)->q, '\"');

	if (single_quotes || double_quotes)
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
			if (*spec != '\'' && *spec != '\"')
			{
				spec = skip_word(&i, str, ps);
				// spec = skip_word(&i, &((*str)->q), &((*str)->eq), ps);
				if (!spec)
					return ;
				if (((*str)->q)[i])
					i++;
			}
			if (*spec == '\'')
			{
				if (check_quot(&i, spec, str, ps))
					return ;
			}
			if (*spec == '\"')
			{
				if (check_quot(&i, spec, str, ps))
					return ;
			}
		}
		(*str)->eq = (*str)->q + i;
		*ps = (*str)->eq;
	}
}

void add_arg(t_list **head, char **q, char **eq)
{
	size_t len;
	char	*str;
	
	len = (*eq - *q);
	str = ft_substr(*q, 0, len);
	ft_lstadd_back(head,ft_lstnew(str, NOTHING));
	// ft_free(&str);
}

bool parse_exec_helper(char **ps, char *es)
{
	int	i;

	i = 0;
	if (skip_and_find(ps, es, "|"))
	{
		while ((*ps + 1)[i] && ft_strchr(WHITESPACE, (*ps + 1)[i]))
			i++;
		if (!(*ps + 1)[i])
		{	
			raise_error("syntax error near unexpected token", 1, '|');
			return (true);
		}
		// if (g_gb.exit_statut == 258)
		// 	return (true);
	}
	return (false);
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

bool	check_tok(int tok)
{
	if (tok != 'a')
	{
		raise_error("syntax test error ", 258, 0);
		return (false);
	}
	return (true);
}

t_cmd	*parseexec(char **ps, char *es, char **envp)
{
	t_cmd			*cmd;
	t_execcmd		*ret;
	int				tok;
	t_ends_of_tok	q_eq;

	cmd = execcmd();
	ret = (t_execcmd *)(cmd);
	ret->args = NULL;
	cmd = parseredirec(ps, es, cmd);
	if (!cmd)
		return (NULL);
	while (!skip_and_find(ps, es, "|"))
	{
		tok = gettoken(ps, es, &q_eq.q, &q_eq.eq);
		if (!tok)
			break ;
		if (!parse_exec_he(&q_eq, ps, &ret->args, es, cmd))
			return (NULL);
	}
	if (parse_exec_helper(ps, es))
		return (NULL);
	return (cmd);
}

t_cmd *parsepipe(char **ps, char *es, char **envp)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = parseexec(ps, es, envp);
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

char check_quotes(char *line)
{
	int		i;	
	char	q;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i];
			i++;
			while (line[i] && line[i] != q)
				i++;
			if (!line[i])
				return (0);
		}
		i++;
	}
	return (1);
}

t_cmd *parser(char **ps, char *es, char **envp)
{
	t_cmd	*cmd;
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (s >= es)
		return (NULL);
	cmd = parsepipe(ps, es, envp);
	clean_arguments(cmd);
	if (g_gb.status)
		return (NULL);
	return (cmd);
}