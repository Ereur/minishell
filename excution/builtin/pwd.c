/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:35:49 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 07:29:58 by aamoussa         ###   ########.fr       */
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
		printf("%s\n", current);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	g_gb.exit_statut = 0;
	return (0);
}
