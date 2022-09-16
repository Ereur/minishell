/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:58:32 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/16 17:52:38 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	raise_error(char *message, int exitcode, int tok)
{
	printf("%s `%c'\n", message, tok);
	gb.exit_satut = exitcode;
	gb.status = 1;
}

int skip_and_find_0(char **ps, char *es)
{
	char	*s;
	int		ret;
	
	s = *ps;
	while(s < es && ft_strchr(WHITESPACE, *s))
		s++;
	return (!*s);
}

// skip spaces and return true in case of finding the given token
int skip_and_find(char **ps, char *es, char *tok)
{
	char	*s;
	int		ret;
	
	s = *ps;
	while(s < es && ft_strchr(WHITESPACE, *s))
		s++;
	ret = *s && ft_strchr(tok, *s);
	return (ret);
}

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

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (s < es)
	{
		if (ft_strchr(SYMBOLE, *s))
			ret = *(ft_strchr(SYMBOLE, *s));
		if (!ft_strchr(SYMBOLE, *s))
			ret = 'a';
		get_token_helper(&s, &ret);
		s++;
		while (s < es && ret == 'a' && !ft_strchr(WHITESPACE, *s) 
			&& !ft_strchr(SYMBOLE, *s))
			s++;
		if (eq)
			*eq = s;
		while (s < es && ft_strchr(WHITESPACE, *s))
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