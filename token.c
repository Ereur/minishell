/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:58:32 by aamoussa          #+#    #+#             */
/*   Updated: 2022/08/23 19:59:51 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void raise_error
// check if there is append rederiction or heredoc and set token type
void	get_token_helper(char **s, int *ret)
{
	char *tmp;

	tmp = *s;
	if (*ret == '<')
	{	
		if (*(tmp + 1) == '<')
		{	
			*ret = '-';
			tmp++;
		}
	}
	if (*ret == '>')
	{	
		if (*(tmp + 1) == '>')
		{	
			*ret = '+';
			tmp++;
		}
	}
	*s = tmp;
}

/* ---define tokens---  https://www.gnu.org/software/bash/manual/html_node/Definitions.html
if there is a pipe | return ==> ascci code of |
Redirection output > return ==> ascii of >
redirection append	>> return ==> +
redirection input <  return ==> <
redirection herdoc	<< return => -
	word return ==> a
	and for the tokens bellow i will them as words 
		( 
		)
		;
		&
*/
int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;
	char	*whitespace;
	char	*symbols;

	symbols = "<|>&";
	whitespace = " \t\r\n\v";
	s = *ps;
	while (s < es && ft_strchr(whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (s < es)
	{
		if (ft_strchr(symbols, *s))
			ret = *(ft_strchr(symbols, *s));
		if (!ft_strchr(symbols, *s))
			ret = 'a';
		get_token_helper(&s, &ret);
		s++;
		while (s < es && ret == 'a' && !ft_strchr(whitespace, *s) 
			&& !ft_strchr(symbols, *s))
			s++;
		if (eq)
			*eq = s;
		while (s < es && ft_strchr(whitespace, *s))
			s++;
		*ps = s;
	}
	return (ret);
}

// test getttoken 

// while ((i = gettoken(&buffer, &buffer[ft_strlen(buffer)], &q, &eq)) && i)
// {
//   char *s;
//   int ret;
// char whitespace[] = " \t\r\n\v";
// char	symbols[] = "<|>&;()";
//   s = *ps;
//   while(s < es && ft_strchr(whitespace, *s))
//     s++;
//   if(q)
//     *q = s;
//   ret = *s;
// //   while (*s)
// //   {
// // 	if ('|' == *s)
	
// //   }
//  
// }