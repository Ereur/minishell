/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:58:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/16 16:30:57 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

void    env(void)
{
	t_senv *head;

	head = gb.env;
    while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}