/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:01:10 by aamoussa          #+#    #+#             */
/*   Updated: 2022/09/13 18:42:36 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstnew(char *content, int state)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (ptr)
	{
		ptr->content = content;
		ptr->state = state;
		ptr->next = NULL;
	}
	return (ptr);
}
