/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:35:49 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/01 11:14:33 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

int	built_in_pwd(char **str, char *current)
{
	char		*pwd;

	if (*str == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_fprintf(1, "%s\n", current);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
