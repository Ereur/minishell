/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:35:49 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/29 15:10:18 by aamoussa         ###   ########.fr       */
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
		printf("%s\n", current);
		return (1);
	}
	else
		reserve = pwd;
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
