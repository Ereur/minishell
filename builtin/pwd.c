/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:35:49 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/08/16 17:12:56 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	built_in_pwd(char **str)
{
	char	*pwd;
	static char *reserve;


	if (*str == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = reserve;
	else
	{
		if (reserve)
			free(reserve);
		reserve = pwd;
	}
	printf("%s\n",pwd);
	free(pwd);
	return (0);
}

int	main(void)
{
	char	*str[2];

	str[0] = "pwd";
	str[1] = NULL;
	built_in_pwd(str);
	return (0);
}
