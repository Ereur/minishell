/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:35:49 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/31 09:55:03 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/parser.h"

int	built_in_pwd(char **str, char *current)
{
	char		*pwd;
	static char	*reserve;

	if (*str == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = reserve;
		ft_fprintf(1, "%s\n", current);
		return (1);
	}
	else
		reserve = pwd;
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
