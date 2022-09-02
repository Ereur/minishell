/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:32 by aamoussa          #+#    #+#             */
/*   Updated: 2022/08/25 21:42:11 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# define EXEC  1
# define REDIR 2
# define PIPE  3
# define SYMBOLE "<|>"
# define WHITESPACE " \t\r\n\v"
# define FORBIDEN_REDIR	"<>|+-"

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd {
	int		type;
	char	*argv[10];
	char	*eargv[10];
}	t_execcmd;

typedef struct s_redircmd {
	int			type;
	t_cmd		*cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}	t_redircmd;

typedef struct s_pipecmd {
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

t_cmd *parsepipe(char **ps, char *es, char **envp);
t_cmd *redirecmd(t_cmd *cmd, char *file, char *efile, int mode, int fd);
t_cmd *execcmd(void);
t_cmd *pipecmd(t_cmd *left, t_cmd *right);

void	nullterminating(t_cmd *cmd);
void	ft_print_som(char *q, char *eq);
void	print_tree(t_cmd *cmd);

#endif