/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:10:59 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/10/29 15:22:50 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// #include "../../minishell.h"
// #include "../../parser/parser.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_envstruct
{
	char				*key;
	char				*value;
	struct s_envstruct	*next;
}	t_senv;

typedef struct s_cord
{
	int				npipe;
	int				cpipe;
	int				i;
	int				mod;
	unsigned long	num;
}t_cord;

/**********************BUILTINS************************/

pid_t	my_fork(void);
void	env(char **arg);
int		exit_cmd(char **args);
int		cd_cmd(char **argument);
int		built_in_pwd(char **str, char *current);
int		ft_echo(char **av);
void	setup_env(char **envp);
t_senv	*env_new(char *str);
void	env_add_back(t_senv **env, t_senv *node);
t_senv	*env_grabber(char *keyword);
int		ft_strcmp(const char *s1, const char *s2);
void	get_envp(void);
int		ft_export(char **args);
int		unset_cmd(char **args);
int		valid_export_name(char *var, int *mode);
int		export_name_exist(char *var, int *mode);
void	export_append(char *var);
void	export_replace(char *var);
void	export_add(char *var, int mode);

/*********************SIGNALS************************/
void	rl_replace_line(const char *text, int clear_undo);
void	signals(void);

/***********************EXIT_CODES******************/
void	waitforcprocess(void);

/***************************************************/
int		ft_strcmp(const char *s1, const char *s2);
int		env_size(void);
t_senv	*env_grabber(char *keyword);
t_senv	*env_new(char *str);
void	env_add_back(t_senv **env, t_senv *node);
/**********************UTILS************************/

#endif 