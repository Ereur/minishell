/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:35:19 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/01 13:21:14 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	convert_list_to_args(t_execcmd *execcmd)
{
	size_t	size;
	int		i;
	t_list	*args;

	i = 0;
	size = ft_lstsize(execcmd->args);
	execcmd->argument = malloc(sizeof(char *) * (size + 1));
	execcmd->argument[size] = NULL;
	// if (!execcmd->args->content)
	// {
	// 	execcmd->argument[i] = NULL;
	// 	// free(execcmd->args);
	// 	return ;
	// }
	while (execcmd->args)
	{	
		if (!execcmd->args->content)
		{
			execcmd->args = execcmd->args->next;
			continue ;
		}
		execcmd->argument[i] = execcmd->args->content;
		args = execcmd->args;
		execcmd->args = execcmd->args->next;
		free(args);
		i++;
	}
	execcmd->argument[i] = NULL;
	free(execcmd->args);
}

char	*merge_list(t_list **head)
{
	t_list	*lst;
	t_list	*tmp;
	char	*next;
	char	*content;
	t_list	*del;

	lst = *head;
	tmp = lst;
	content = NULL;
	put_zero_in_null(&content);
	if (tmp)
	{	
		while (tmp->next)
		{	
			next = (tmp->next)->content;
			(tmp->next)->content = ft_strjoin(tmp->content,
					(tmp->next)->content);
			ft_free(&(next));
			del = tmp;
			tmp = tmp->next;
			ft_free(&del->content);
			free(del);
		}
		ft_free(&content);
		content = ft_strdup(tmp->content);
		ft_free(&tmp->content);
		free(tmp);
	}
	return (content);
}

void	split_dollar(t_list *args, int counter)
{
	t_list	*tmp;
	t_list	*lst_of_dollar;
	int		i;
	char	*arg;
	char	*hold;

	i = 0;
	tmp = args;
	lst_of_dollar = NULL;
	while (tmp)
	{
		i = 0;
		if (tmp->state == SQ)
		{
			tmp = tmp->next;
			continue ;
		}
		arg = tmp->content;
		while (arg[i])
			collect_var(&lst_of_dollar, &i, arg, tmp);
		expand_lst(lst_of_dollar, counter);
		hold = tmp->content;
		if (!lst_of_dollar->content)
		{
			ft_free(&tmp->content);
			tmp->content = NULL;
			tmp = tmp->next;
			continue ;
		}
		tmp->content = merge_list(&lst_of_dollar);
		ft_free(&hold);
		lst_of_dollar = NULL;
		tmp = tmp->next;
	}
}

void	collect_sq_and_dq(t_list **split_args, char *line, char q)
{
	char	*content;
	int		i;

	i = 0;
	while (line[i])
	{
		collect_word(split_args, line, &i, q);
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
		{
			q = line[i];
			content = ft_substr(line, i + 1, count_len(i, line, line[i]));
			ft_lstadd_back(split_args, ft_lstnew(content, q));
			i += count_len(i, line, line[i]) + 1;
		}
		if (!line[i])
			break ;
		i++;
	}
}

void	make_quotes(t_list	*args, bool i, int counter)
{
	t_list		*split_args;
	char		q;
	char		*line;
	t_list		*tmp;

	tmp = args;
	while (tmp)
	{
		split_args = NULL;
		line = tmp->content;
		if (ft_strlen(line) == 1 && line[0] == '$')
		{	
			tmp = tmp->next;
			continue ;
		}
		q = '\"';
		collect_sq_and_dq(&split_args, line, q);
		if (i)
			split_dollar(split_args, counter);
		if (!split_args->content)
		{
			tmp->content = NULL;
			tmp = tmp->next;
			continue;
			// ft_free(&tmp->content);
		}
		ft_free(&tmp->content);
		tmp->content = merge_list(&split_args);
		tmp = tmp->next;
	}
}
