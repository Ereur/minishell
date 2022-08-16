/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:08:30 by aamoussa          #+#    #+#             */
/*   Updated: 2021/11/14 21:51:34 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int	counter;

	counter = 1;
	if (lst == NULL)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}
