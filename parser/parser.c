/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:06:38 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/02 04:24:56 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void print_tree(t_cmd *cmd)
// {
// 	t_execcmd *execcm;
// 	t_redircmd *redir;
// 	t_pipecmd	*pipe;

// 	int i;
// 	i = 0;
// 	// if (!cmd)
// 	// 	return ;
// 	// if (cmd->type == REDIR)
// 	// {
// 	// 		redir = (t_redircmd *)(cmd);
// 	// 		printf("\n----------redirection-------\n");
// 	// 		// ft_print_som(redir->file, redir->efile);
// 	// 		printf("|%s|\n", redir->filee->content);
// 	// 		printf("fd %d\n", redir->fd);
// 	// 		printf(" \nmode %d\n", redir->mode);
// 	// 		print_tree(redir->cmd);
// 	// }
// 	if (cmd->type == EXEC)
// 	{
// 		int	i;

// 		i = 0;
// 		execcm = (t_execcmd	*)(cmd);
// 		t_list *tmp;

// 		tmp = execcm->args;
// 		printf("\n----------Arguments-------\n");
// 		// while (tmp)
// 		// {	
// 		// 	// ft_print_som(execcm->argv[i], execcm->eargv[i]);
// 		// 	// write(1,&execcm->argv[i], ft_strlen(execcm->argv[i]));
// 		// 	printf("|%s|\n", tmp->content);
// 		// 	tmp = tmp->next;
// 		// }
// 		while (execcm->argument && execcm->argument[i])
// 		{
// 			printf("|%s|\n",execcm->argument[i]);
// 			i++;
// 		}
// 		printf("output : %d \n input : %d \n", execcm->output, execcm->input);
// 	}
// 	if (cmd->type == PIPE)
// 	{
// 		pipe = (t_pipecmd *)(cmd);
// 		printf("\nPIPE\n");
// 		print_tree(pipe->left);
// 		print_tree(pipe->right);
// 	}
// }

void	add_arg(t_list **head, char **q, char **eq)
{
	size_t	len;
	char	*str;

	len = (*eq - *q);
	str = ft_substr(*q, 0, len);
	ft_lstadd_back(head, ft_lstnew(str, NOTHING));
}

bool	parse_exec_helper(char **ps, char *es, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (skip_and_find(ps, es, "|"))
	{
		while ((*ps + 1)[i] && ft_strchr(WHITESPACE, (*ps + 1)[i]))
			i++;
		if (!(*ps + 1)[i])
		{	
			raise_error("syntax error near unexpected token", 1, '|', cmd);
			return (true);
		}
	}
	return (false);
}

t_cmd	*parseexec(char **ps, char *es, char **envp)
{
	t_cmd			*cmd;
	t_execcmd		*ret;
	int				tok;
	t_ends_of_tok	q_eq;

	cmd = execcmd();
	ret = (t_execcmd *)(cmd);
	ret->args = NULL;
	cmd = parseredirec(ps, es, cmd);
	if (!cmd)
		return (NULL);
	while (!skip_and_find(ps, es, "|"))
	{
		tok = gettoken(ps, es, &q_eq.q, &q_eq.eq);
		if (!tok)
			break ;
		if (!parse_exec_he(&q_eq, ps, &ret->args, es, cmd))
			return (NULL);
	}
	if (parse_exec_helper(ps, es, cmd))
		return (NULL);
	return (cmd);
}

t_cmd	*parsepipe(char **ps, char *es, char **envp)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = parseexec(ps, es, envp);
	if (!cmd)
		return (NULL);
	if (skip_and_find(ps, es, "|"))
	{	
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es, envp));
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_cmd	*parser(char **ps, char *es, char **envp)
{
	t_cmd	*cmd;
	char	*s;
	int		counter;

	counter = 0;
	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (s >= es)
		return (NULL);
	cmd = parsepipe(ps, es, envp);
	clean_arguments(cmd, &counter);
	if (g_gb.status)
		return (NULL);
	return (cmd);
}
