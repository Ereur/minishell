/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:32 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/03 07:43:58 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
# include "../excution/utils/execution.h"
# define EXEC  1
# define REDIR 2
# define PIPE  3
# define SYMBOLE "<|>"
# define WHITESPACE " \t\r\n\v"
# define FORBIDEN_REDIR	"<>|+-"
# define DQ '\"'
# define SQ '\''
# define NOTHING 0
# define REMOVEQUOTE 1
# define EXPAND 2

typedef struct s_gb_variable
{
	char	**envp;
	t_senv	*env;
	int		status;
	int		exit_statut;
	int		npipe;
	int		fd_input_prev;
	pid_t	last_pid;
	int		input;
	int		output;
	int		here_doc;
	char	*curent;
}	t_gb_variable;

t_gb_variable	g_gb;

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

typedef struct s_ends_of_buff
{
	char	**ps;
	char	*es;
}	t_ends_of_buff;

typedef struct s_ends {
	t_ends_of_tok	q_and_eq;
	t_ends_of_buff	buff;
}	t_ends;

typedef struct s_tok_cmd
{
	t_cmd	*cmd;
	int		tok;
}	t_tok_cmd;

typedef struct s_counter_start {
	int	start;
	int	counter;

}	t_counter_start;

int		checifbuiltin(t_execcmd *exec);
void	execute_cmd(t_execcmd *cmd);

void	raise_error(char *message, int exitcode, int tok, t_cmd *cmd);
void	free_args_list(t_list **args);
void	free_cmd(t_cmd *cmd);
void	split_dollar(t_list *args, int counter);
void	here_doc_expander(char **here_doc_lim, bool i);
void	quotes_pareser(t_ends_of_tok **str, char **ps, t_cmd *cmd);
void	convert_list_to_args(t_execcmd *execcmd);
char	*grep_variable(char *str, int counter);
int		count_len(int i, char *line, char q);
void	collect_word(t_list **split_args, char *line, int *i, char q);
void	make_quotes(t_list	*args, bool i, int counter);
void	word_len(char *arg, int *i, int *len);
void	collect_var(t_list **lst_of_dollar, int *i, char *arg, t_list *tmp);
void	expand_lst(t_list *dollars, int counter);
t_cmd	*parseredirec(char **ps, char *es, t_cmd *cmd);
t_cmd	*parse_exec_he(t_ends_of_tok *q_eq, t_list **args,
			t_ends_of_buff *ps_es, t_cmd *cmd);
t_cmd	*parsepipe(char **ps, char *es, char **envp);
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
int		here_doc(char *lim, bool falg);
int		cd_cmd(char **argument);
void	execute_builtins(t_cmd *cmd);
void	executer(t_cmd *cmd);
void	clean_arguments(t_cmd *cmd, int *counter);
int		skip_dollar(char *test);
int		find_name(char *s);
void	put_zero_in_null(char **str);
void	add_arg(t_list **head, char **q, char **eq);
char	*ft_strncpy(char *dest, char *src, unsigned int n);	
void	nullterminating(t_cmd *cmd);
t_cmd	*parser(char **ps, char *es, char **envp);
void	print_tree(t_cmd *cmd);

// trying
void	pipe_executer(t_cmd *first_cmd, t_cmd *cmd, int npipe, int cpipe);
void	close_all_fds(t_cmd *cmd);
void	excute_pipes(t_cmd *cmd, int flag);
void	sig_handler(int signal);
void	error_displayer(t_execcmd *cmd);
void	rl_replace_line(const char *text, int clear_undo);
int		checkbuiltprotection(t_execcmd *exec);
/******************redir_utils***********/
bool	check_tok(int tok, t_cmd *cmd);
bool	protect_redir_input(char *file, t_execcmd *exec, char *tmp, int fd);
bool	parse_input_redir(t_ends_of_buff *buff, t_ends_of_tok *str,
			t_execcmd *exec, t_tok_cmd *tok_cmd);
bool	protect_output_redir(char *file, t_execcmd *exec, char *tmp, int fd);
bool	parse_output_redir(t_ends_of_buff *buff, t_ends_of_tok *str,
			t_execcmd *exec, t_tok_cmd *tok_cmd);
/****************shellutils**********/
/****************************************/
bool	clen_arguments_helper(t_execcmd *execcmd, int counter);
void	clean_arguments(t_cmd *cmd, int *counter);
void	collect_sq_and_dq(t_list **split_args, char *line, char q);
void	make_quotes(t_list	*args, bool i, int counter);
char	*merge_list(t_list **head);
/*****************herdoc************/
void	sig_handl(int signal);
int		get_first_line(int *end, char *lim, bool flag);
void	here_doc_expand(char **line, bool i);
int		protect_first_sig(int end[2], char *line);
/**********************parser_utils***********/
void	add_arg(t_list **head, char **q, char **eq);

#endif