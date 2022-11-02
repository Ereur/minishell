/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cleaner_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:43:20 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/02 15:41:48 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	expand(int len, t_list *tmp, int i, t_counter_start star_counter)
{
	char	*content;
	char	*str;
	char	*free_content;

	str = NULL;
	if (len > 1)
		str = ft_substr(tmp->content, star_counter.start, len - 1);
	content = grep_variable(&tmp->content[i], star_counter.counter);
	if (!content)
	{	
		ft_free(&str);
		ft_free(&tmp->content);
		tmp->content = content;
		return ;
	}
	free_content = content;
	put_zero_in_null(&str);
	content = ft_strjoin(str, content);
	ft_free(&tmp->content);
	ft_free(&str);
	ft_free(&free_content);
	tmp->content = content;
}

void	expand_lst(t_list *dollars, int counter)
{
	t_list			*tmp;
	t_counter_start	start_counter;
	int				i;
	int				len;

	tmp = dollars;
	start_counter.counter = counter;
	while (tmp)
	{
		if (!ft_strchr(tmp->content, '$'))
		{
			tmp = tmp->next;
			continue ;
		}
		i = 0;
		start_counter.start = i;
		len = 0;
		while (tmp->content[i++] == '$')
			len++;
		i--;
		expand(len, tmp, i, start_counter);
		tmp = tmp->next;
	}
}

void	collect_var(t_list **lst_of_dollar, int *i, char *arg, t_list *tmp)
{
	int		len;
	int		start;
	char	*content;

	start = (*i);
	len = 0;
	content = NULL;
	word_len(arg, i, &len);
	if (len)
	{
		content = ft_substr(arg, start, len);
		ft_lstadd_back(lst_of_dollar, ft_lstnew(content, tmp->state));
	}	
	if (arg[*i] == '$')
	{
		start = (*i);
		len = skip_dollar(&arg[*i])
			+ find_name(&arg[skip_dollar(&arg[*i]) + (*i)]);
		content = ft_substr(arg, start, len);
		ft_lstadd_back(lst_of_dollar, ft_lstnew(content, tmp->state));
		(*i) += len;
	}
}

int	count_len(int i, char *line, char q)
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

void	collect_word(t_list **split_args, char *line, int *i, char q)
{
	int		counter;
	int		start;
	char	*content;

	counter = 0;
	start = 0;
	content = NULL;
	if (line[*i] != q)
	{
		start = *i;
		counter = 0;
		while (line[*i] && line[*i] != '\"')
		{
			if (line[*i] == '\'')
				break ;
			(*i)++;
			counter++;
		}
		if (counter != 0)
		{	
			content = ft_substr(line, start, counter);
			ft_lstadd_back(split_args, ft_lstnew(content, NOTHING));
		}
	}
}
