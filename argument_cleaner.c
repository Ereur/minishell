/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:13:53 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/15 17:06:23 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



int	count_len(int i, char *line ,char q)
{
	int		size;

	size = 0;
	i++;
	while (line[i] != q)
	{
		size++;
		i++;
	}

	return (size);
}

char *grep_name(char *s)
{
	char *tmp;
	char *name;
	int  i;

	i = 0;
	tmp = s;
	if (!*s)
		return (s);
	name = NULL;
	while (*tmp)
	{
		if (!ft_isalpha(*tmp) && *tmp!='_')
			break;
		tmp++;
		i++;
	}
	name = (char *)malloc(i + 2);
	name = ft_strncpy(name, s, i);
	name[i + 1] = 0;
	name[i] = '=';
	return (name);
}

char *grep_variable(char *str)
{
	char *name;
	int		i;
	char	*variabl;

	i = 0;
	name = grep_name(str);
	if (!*name)
		return (name);
	variabl = NULL;
	while (variable.envp[i])
	{
		if (ft_strnstr(variable.envp[i], name, ft_strlen(variable.envp[i])))
			break;
		i++;
	}
	if(variable.envp[i])
		variabl = (ft_strchr(variable.envp[i], '=') + 1);
	put_zero_in_null(&variabl);
	return (variabl);
}

void expand_lst(t_list *dollars)
{
	t_list	*tmp;
	int		start;
	int		i;
	int		len;
	char	*str;
	char	*content;

	i = 0;
	tmp = dollars;
	len = 0;
	str = NULL;

	while (tmp)
	{
		if (!ft_strchr(tmp->content,'$'))
		{
			tmp = tmp->next;
			continue;
		}
		i = 0;
		start = i;
		len = 0;
		str = NULL;
		while (tmp->content[i++] == '$')
			len++;
		i--;
		if (len > 1)
			str = ft_substr(tmp->content, start, len - 1);
		content = grep_variable(&tmp->content[i]);
		put_zero_in_null(&str);
		content	= ft_strjoin(str,content);
		tmp->content = content;
		tmp = tmp->next;
	}
}

char *merge_list(t_list **head)
{
	t_list *lst;
	t_list	*tmp;
	char	*content;
	
	lst = *head;
	tmp = lst;
	content = NULL;
	put_zero_in_null(&content);
	if (tmp)
	{	
		while (tmp->next)
		{
			(tmp->next)->content = ft_strjoin(tmp->content, (tmp->next)->content);
			tmp = tmp->next;
		}
		content = ft_strdup(tmp->content);
	}
	return (content);
}

void split_dollar(t_list *args)
{
	t_list *tmp;
	t_list *lst_of_dollar;
	
	int		i;
	char	*arg;
	char	*content;
	int		start;
	int		len;

	i = 0;
	tmp = args;
	lst_of_dollar = NULL;
	while (tmp)
	{
		i = 0;
		if (tmp->state == SQ)
		{
			tmp = tmp->next;
			continue;
		}
		arg = tmp->content;
		while (arg[i])
		{
			start = i;
			len = 0;
			while (arg[i] && arg[i] != '$')
			{	
				len++;
				i++;
			}
			if (len)
			{
				content = ft_substr(arg, start, len);
				ft_lstadd_back(&lst_of_dollar, ft_lstnew(content, tmp->state));
			}	
			if (arg[i] == '$')
			{
				start = i;
				len = skip_$(&arg[i]) + find_name(&arg[skip_$(&arg[i]) + i]);
				content = ft_substr(arg, start, len);
				ft_lstadd_back(&lst_of_dollar, ft_lstnew(content, tmp->state));
				i += len;
			}
			
		}
		expand_lst(lst_of_dollar);
		tmp->content = merge_list(&lst_of_dollar);
		lst_of_dollar = NULL;
		tmp = tmp->next;
	}
	
}

void make_quotes(t_cmd *cmd)
{
	t_execcmd	*args;
	t_list		*split_args;
	int			i;
	char		q;
	char		*line;
	char		*content;
	int			start;
	int			counter;
	t_list		*tmp;

	
	args = (t_execcmd *)cmd;
	if (!check_quotes(args->args->content))
		raise_error("syntax error unclosed quotes", 1, 0);

	tmp = args->args;
	while (tmp)
	{
		split_args = NULL;
		i = 0;
		line = tmp->content;
		q = '\"';
		while (line[i])
		{
			
			if (line[i] != q)
			{
				start = i;
				counter = 0;
				while (line[i] && line[i] != '\"')
				{
					if (line[i] == '\'')
						break;
					i++;
					counter++;
				}
				if (counter != 0)	
				{	
					content = ft_substr(line, start, counter);
					ft_lstadd_back(&split_args, ft_lstnew(content, NOTHING));
				}
			}
			if (line[i] && (line[i] == '\'' || line[i] == '\"'))
			{
				q = line[i];
				content = ft_substr(line, i + 1, count_len(i, line, line[i]));
				ft_lstadd_back(&split_args, ft_lstnew(content, q));
				i += count_len(i, line, line[i]) + 1;
			}
			if (!line[i])
				break;
			i++;
		}
		split_dollar(split_args);
		tmp->content = merge_list(&split_args);
		tmp = tmp->next;
	}
	// while(split_args)
	// {
	// 	printf("%s state : %c\n", split_args->content, split_args->state);
	// 	split_args = split_args->next;
	// }
}

void clean_arguments(t_cmd *cmd)
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
		execcmd = (t_execcmd *)cmd;
		make_quotes(cmd);
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redircmd *)cmd;
		*redir->efile = 0;
		clean_arguments(redir->cmd);
		// nullterminating(redir->cmd);
	}
	if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)(cmd);
		clean_arguments(pipecmd->left);
		clean_arguments(pipecmd->right);
	}
}