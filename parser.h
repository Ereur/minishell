/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:32 by aamoussa          #+#    #+#             */
/*   Updated: 2022/10/27 14:19:51 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "./excution/utils/execution.h"
// # include ".git/exe"
# define EXEC  1
# define REDIR 2
# define PIPE  3
# define SYMBOLE "<|>"
# define WHITESPACE " \t\r\n\v"
# define FORBIDEN_REDIR	"<>|+-"
# define	DQ '\"'
# define	SQ '\''
# define	NOTHING 0

typedef struct s_g_gb_variable
{
	char	**envp;
	t_senv	*env;
	int		status;
	int		exit_statut;
	int		npipe;
	int		fd_input_prev;
	pid_t	last_pid;
	int		fdg;
	int		input;
	int		output;
}	t_g_gb_variable;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd {
	int		type;
	t_list	*args;
	int		output;
	int		input;
	char	**argument;		
}	t_execcmd;

typedef struct s_redircmd {
	int			type;
	t_cmd		*cmd;
	t_list		*filee;
	int			mode;
	int			fd;
}	t_redircmd;

typedef struct s_pipecmd {
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_ends_of_tok
{
	char	*q;
	char	*eq;
}	t_ends_of_tok;

t_g_gb_variable	g_gb;

int		checifbuiltin(t_execcmd *exec);
void	execute_cmd(t_execcmd *cmd);

int		here_doc(char *);
t_cmd	*parsepipe(char **ps, char *es, char **envp);
t_cmd	*redirecmd(t_cmd *cmd, char *file, char *efile, int mode, int fd);
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
int		here_doc(char *lim);
int     cd_cmd(char **argument);
void	execute_builtins(t_cmd *cmd);
void    executer(t_cmd *cmd);
char	check_quotes(char *line);
void	clean_arguments(t_cmd *cmd);
int		skip_dollar(char *test);
int		find_name(char *s);
void 	put_zero_in_null(char **str);
void 	add_arg(t_list **head, char **q, char **eq);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	nullterminating(t_cmd *cmd);
void	ft_print_som(char *q, char *eq);
t_cmd	*parser(char **ps, char *es, char **envp);
void	print_tree(t_cmd *cmd);

// trying
//trying
void	pipe_executer(t_cmd *first_cmd, t_cmd *cmd , int npipe, int cpipe);
void	close_all_fds(t_cmd *cmd);
void 	excute_pipes(t_cmd *cmd, int flag);
void	sig_handler(int signal); 
#endif