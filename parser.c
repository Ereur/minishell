/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:06:38 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/16 18:16:04 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *find_dq(char **q, char **eq, char *es)
// {
// 	char *ret;

// 	ret = ft_strchr(*q, '\"');
// 	while (ret)
// 	{
		
// 	}	
// }

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
	while (*tmp)
	{
		if (!ft_isalpha(*tmp) && *tmp!='_')
			break;
		tmp++;
		i++;
	}
	// name = (char *)malloc(i + 2);
	// name = ft_strncpy(name, s, i);
	// name[i + 1] = 0;
	// name[i] = '=';
	return (i);
}

int skip_$(char *str)
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

// char *find_first(char *str)
// {
// 	char *ret;
// 	char tmp[0];
// 	char *first;

// 	ret = ft_strchr(str, '$');
// 	ret = ret + skip_$(ret);
// 	tmp[0] = *ret;
// 	*ret = 0;
// 	first = ft_strdup(str);
// 	*ret = tmp[0];
// 	return (first);
// }

// char *join_all(char *first, char *sec, char *third)
// {
// 	char *str;

// 	if (!sec)
// 	{	
// 		sec = (char *)malloc(1);
// 		sec[0] = 0;
// 	}
// 	if (!first)
// 	{
// 		first = (char *)malloc(1);
// 		first[0] = 0;
// 	}
// 	if(!third)
// 	{
// 		third = (char *)malloc(1);
// 		third[0] = 0;
// 	}
// 	str = ft_strjoin(first, sec);
// 	str = ft_strjoin(str, third);
// 	return (str);
// }



// int	expand_dq(char **q, char **eq, char **envp)
// {
// 	char *ret;
// 	char tmp[0];
// 	char *name;
// 	char *first;
// 	int		i;
// 	char	*variabl;
// 	char	*after;

// 	i = 0;
// 	ret = NULL;
// 	variabl = NULL;
// 	first = NULL;
// 	tmp[0] = *eq[0];
// 	name = NULL;
// 	*eq[0] = 0;
// 	ret = ft_strchr(*q, '$');
// 	if (ret)
// 	{	
// 		ret = ret + skip_$(ret);
// 		first = find_first(*q);
// 		first[ft_strlen(first) - 1] = 0;
// 		name = find_name(ret, &after);
// 		while (envp[i])
// 		{
// 			if (ft_strnstr(envp[i], name, ft_strlen(envp[i])))
// 				break;
// 			i++;
// 		}
// 		printf("test : %s\n",*q);
// 		if(envp[i])
// 		{	
// 			variabl = (ft_strchr(envp[i], '=') + 1);
// 		}
// 		ret = ret + (ft_strlen(name) - 1);
// 		*q = join_all(first, variabl, ret);
		
// 	}
// 	else 
// 		return (0);
// 	expand_dq(q, eq, envp);
// 	return (1);
// }
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

// void expand_dq(char **q, char **eq, char **envp)
// {
// 	char *scanning;
// 	char *variable_name;
// 	size_t scanning_lenght;
// 	char	*result;
// 	int		i;
// 	char	*value;

// 	i = 0;
// 	result = NULL;
// 	variable_name = NULL;
// 	scanning = NULL;
// 	value = NULL;
// 	while (scanning < *eq)
// 	{
// 		scanning = ft_strchr(*q, '$');
// 		if (!scanning)
// 			break;
// 		scanning = scanning + skip_$(*q);
// 		variable_name = find_name(scanning);
// 		scanning_lenght = scanning - *q;	
// 		scanning = scanning + (ft_strlen(variable_name) - 1);
// 		i = 0;
// 		while (envp[i])
// 		{
// 			if (ft_strnstr(envp[i], variable_name, ft_strlen(envp[i])))
// 				break;
// 			i++;
// 		}
// 		printf("test : %s\n",*q);
//  	if(envp[i])
// 		{	
// 			value = (ft_strchr(envp[i], '=') + 1);
// 		}
// 		result = join(*q, scanning_lenght - 1, value, result);
// 		*q = scanning;
// 	}
// 	if (result)
// 		*q = ft_strjoin(result, *q);
// }

void quote_parser(char **q, char **eq, char *quote_type, char **ps, char **envp)
{
	char *ret;
	char *str;
	char *double_quotes;
	str = "<|> \t\r\n\v";
	char	*estr;
	char tmp[0];
	
	ret = NULL;
	estr = NULL;
	double_quotes = NULL;
	tmp[0] = *eq[0];
	*eq[0] = 0;
	double_quotes = ft_strchr(*q, *quote_type);
	if (!double_quotes)
	{	
		*eq[0] = *tmp;
		return;
	}
	*eq[0] = *tmp;
	ret = ft_strchr((ft_strchr(*q, *quote_type) + 1), *quote_type);
	if (!ret)
	{	
		raise_error("syntax error unclosed quotes", 258, 0);
		*q = NULL;
		return ;
	}
	if (ret)
	{	
		ret = ret + 1;
		while (*str)
		{
			estr = ft_strchr(ret , *str);
			if (estr)
				break;
			str++;
		}
		if (!*str)
			ret = ft_strchr(ret , *str);
		else
			ret = estr;	
		*eq = ret;
		*ps = ret;
		// expand_dq(q, eq, envp);
	}
}

// void nullterminating(t_cmd *cmd)
// {
// 	t_execcmd	*execcmd;
// 	t_redircmd	*redir;
// 	t_pipecmd	*pipecmd;
// 	int			i;

// 	i = 0;
// 	if (!cmd)
// 		return ;
// 	if (cmd->type == REDIR)
// 	{
// 		redir = (t_redircmd *)cmd;
// 		nullterminating(redir->cmd);
// 	}
// 	if (cmd->type == PIPE)
// 	{
// 		pipecmd = (t_pipecmd *)(cmd);
// 		nullterminating(pipecmd->left);
// 		nullterminating(pipecmd->right);
// 	}
// }

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
	if (cmd->type == REDIR)
	{
			redir = (t_redircmd *)(cmd);
			printf("\n----------redirection-------\n");
			// ft_print_som(redir->file, redir->efile);
			printf("|%s|\n", redir->filee->content);
			printf("fd %d\n", redir->fd);
			printf(" \nmode %d\n", redir->mode);
			print_tree(redir->cmd);
	}
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
		while (execcm->argument[i])
		{
			printf("|%s|\n",execcm->argument[i]);
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
			{	
				raise_error("syntax error near unexpected token", 258, tok);
				return (NULL);
			}
			cmd = redirecmd(cmd, q, eq, O_RDONLY, 0);
		}
		else if ('>')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
			{	
				raise_error("syntax error near unexpected token", 258, tok);
				return (NULL);
			}
			cmd = redirecmd(cmd, q, eq, O_RDWR|O_TRUNC|O_CREAT, 1);
		}
		else if ('-')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
			{	
				raise_error("syntax error near unexpected token", 258, tok);
				return (NULL);
			}
			cmd = redirecmd(cmd, q, eq, O_RDONLY, 0);
		}
		else if ('+')
		{
			tok = gettoken(ps, es, &q, &eq);
			if (ft_strchr(FORBIDEN_REDIR, tok))
			{	
				raise_error("syntax error near unexpected token", 1, tok);
				return (NULL);
			}
			cmd = redirecmd(cmd, q,eq, O_RDWR|O_CREAT, 1);
		}
	}
	return (t_cmd *)(cmd);
}


void quotes_pareser(char **q, char **eq, char **ps, char **envp)
{
	char *single_quotes;
	char *double_quotes;
	
	single_quotes = ft_strchr(*q, '\'');
	double_quotes = ft_strchr(*q, '\"');

	if (single_quotes && double_quotes)
	{	
		if (single_quotes < double_quotes)
		{	
			quote_parser(q, eq, "\'", ps, envp);
			if (!q)
				return ;
		}
		else if (double_quotes > single_quotes)
		{	
			quote_parser(q, eq, "\"", ps, envp);
			if (!q)
				return ;
		}
	}
	else
	{
		if (single_quotes)
		{	
			quote_parser(q, eq, "\'", ps, envp);
			if (!q)
				return ;
		}
		if (double_quotes)
		{	
			quote_parser(q, eq, "\"", ps, envp);
			if (!q)
				return ;
		}
	}
}

void add_arg(t_list **head, char **q, char **eq)
{
	size_t len;
	char	*str;
	
	len = (*eq - *q);
	str = ft_substr(*q, 0, len);
	ft_lstadd_back(head,ft_lstnew(str, NOTHING));
}

t_cmd *parseexec(char **ps, char *es, char **envp)
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
	ret->args = NULL;
	cmd = parseredirec(ps, es, cmd);
	if (!cmd)
		return (NULL);
	if (skip_and_find(ps,es, "|"))
	{		
		raise_error("syntax error near unexpected token", 258, '|');
		if (gb.exit_statut == 258)
			return (NULL);
	}
	// if(skip_and_find_0(ps, es))
	// 		raise_error("syntax error near unexpected token", 1, '|');
	while (!skip_and_find(ps , es, "|"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (!tok)
			break;
		// skip_and_find_quotes(ps, );
		if (tok != 'a')
		{
			raise_error("syntax error ", 258, 0);
			return (NULL);
		}
		quotes_pareser(&q, &eq, ps, envp);
		if (!q)
			return (NULL);
		add_arg(&ret->args, &q, &eq);
		// ret->argv[argc] = q;
		// ret->eargv[argc] = eq;
		argc++;
 		cmd = parseredirec(ps ,es, cmd);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_cmd *parsepipe(char **ps, char *es, char **envp)
{
	t_cmd	*cmd;
	cmd = NULL;
	cmd = parseexec(ps, es, envp);
	if (!cmd)
		return (NULL);
	if (skip_and_find(ps , es, "|"))
	{	
		gettoken(ps , es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es, envp));
		if (!cmd)
			return (NULL);
		// printf("hehe%d\n", cmd->type);
	}
	return (cmd);
}

char check_quotes(char *line)
{
	int i;	
	char q;

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
	t_cmd *cmd;
	
	cmd = parsepipe(ps, es, envp);
	clean_arguments(cmd);
	if (gb.status)
		return (NULL);
	return (cmd);
}
