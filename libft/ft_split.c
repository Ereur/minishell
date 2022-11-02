/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:20:13 by aamoussa          #+#    #+#             */
/*   Updated: 2021/11/23 15:21:29 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(char *b, char c)
{
	int		i;
	int		counter;

	if (!*b)
		return (0);
	i = 0;
	counter = 0;
	while (b[i])
	{
		if (b[i] == c && !(b[i + 1] == c))
		{
			counter++;
		}
		i++;
	}
	return (counter + 1);
}

static	void	ft_free_all(char **ptr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

static void	ft_strs_len(char *s, char c, char **ptr)
{
	int		i;
	int		counter;
	int		j;

	i = 0;
	j = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i] && !(s[i++] == c))
			counter++;
		ptr[j] = malloc((counter + 1) * sizeof(char));
		if (!(ptr[j++]))
		{	
			ft_free_all(ptr, j);
			ptr = NULL;
			return ;
		}
	counter = 0;
	}
	ptr[j] = NULL;
}

static char	**ft_fill_strs(char *s, char c, char **ptr)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	i = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i] && !(s[i] == c))
		{
			ptr[j][k] = s[i];
			i++;
			k++;
		}
		ptr[j][k] = 0;
		j++;
	}
	free(s);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char		**ptr;
	int			num_of_words;
	char		*trimd;
	char		tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	if (!s)
		return (NULL);
	trimd = ft_strtrim(s, tmp);
	if (!trimd)
		return (NULL);
	num_of_words = ft_counter(trimd, c) + 1;
	ptr = malloc(num_of_words * sizeof(char *));
	if (!ptr)
	{	
		free(trimd);
		return (NULL);
	}
	ft_strs_len(trimd, c, ptr);
	if (!ptr)
		return (NULL);
	return (ft_fill_strs(trimd, c, ptr));
}
