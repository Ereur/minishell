/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:23:53 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/03 03:32:29 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	find_name(char *s)
{
	char	*tmp;
	char	*name;
	int		i;

	i = 0;
	tmp = s;
	name = NULL;
	if (*tmp == '?')
		return (1);
	if (ft_isdigit(*tmp))
	{	
		i++;
		return (i);
	}
	while (*tmp)
	{
		if (*tmp == '_' || ft_isalnum(*tmp))
		{
			tmp++;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	put_zero_in_null(char **str)
{
	char	*tmp;

	tmp = NULL;
	tmp = *str;
	if (!tmp)
	{
		tmp = (char *)malloc(1);
		tmp[0] = 0;
	}
	*str = tmp;
}

int	skip_dollar(char *str)
{
	int	i;

	i = 0;
	str = ft_strchr(str, '$');
	while (str && *str == '$')
	{
		str++;
		i++;
	}
	return (i);
}
