/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:10:59 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/16 17:30:13 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "../../minishell.h"

#include <stdio.h>
#include <string.h>

typedef struct s_envstruct
{
    char *key;
    char *value;
    struct s_envstruct *next;
} t_senv;

void    env(void);
void	setup_env(char **envp);
t_senv	*env_new(char *str);
void	env_add_back(t_senv **env, t_senv *node);
t_senv	*env_grabber(char *keyword);
int	    ft_strcmp(const char *s1, const char *s2);

#endif 