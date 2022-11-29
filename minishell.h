/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:11:41 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/03 08:00:56 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <stdio.h>
# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "excution/utils/execution.h"
# include "./parser/parser.h"
# include "./parser/token.h"
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

int			built_in_pwd(char **str, char *current);
const char	*getprompt(char **envp);
pid_t		fork_process(void);

#endif