/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/16 17:38:15 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

int cd(char **argument)
{
	t_senv *home;

  if (!argument[1])
  {
	home = env_grabber("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home->value))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
  }
if (chdir(argument[1]))
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(argument[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}
  
  return (0);
}

