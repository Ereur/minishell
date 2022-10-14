/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:43:08 by aamoussa          #+#    #+#             */
/*   Updated: 2022/10/14 16:43:46 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *redirecmd(t_cmd *cmd, char *file, char *efile, int mode, int fd)
{
	// t_redircmd	*root;
	// t_list		*filee;
	t_execcmd	*root;
	root = (t_execcmd *)cmd;
	close(root->output);
	// root = malloc(sizeof(t_redircmd));
	// root->filee = NULL;
	// ft_memset(root, 0, sizeof(t_redircmd *));
	// add_arg(&root->filee, &file, &efile);
	// root->mode = mode;
	// root->type = REDIR;
	// root->cmd = cmd;
	// root->fd = fd;
	
	return (t_cmd *)(root);
}

t_cmd *execcmd(void)
{
	t_execcmd *cmd;

	cmd = malloc(sizeof(t_execcmd));
	ft_memset(cmd, 0, sizeof(t_execcmd *));
	cmd->type = EXEC;
	cmd->output = 1;
	cmd->input = 0;
	return (t_cmd *)(cmd);
}

t_cmd *pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd *root;
	
	root = malloc(sizeof(t_pipecmd));
	ft_memset(root, 0, sizeof(t_pipecmd *));
	root->type = PIPE;
	root->left = left;
	root->right = right;
	return (t_cmd *)(root);
}