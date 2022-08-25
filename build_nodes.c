/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:43:08 by aamoussa          #+#    #+#             */
/*   Updated: 2022/08/25 04:11:32 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *redirecmd(t_cmd *cmd, char *file, char *efile, int mode, int fd)
{
	t_redircmd	*root;
	
	root = malloc(sizeof(t_redircmd));
	ft_memset(root, 0, sizeof(t_redircmd *));
	root->file = file;
	root->efile = efile;
	root->mode = mode;
	root->type = REDIR;
	root->cmd = cmd;
	root->fd = fd;
	return (t_cmd *)(root);
}

t_cmd *execcmd(void)
{
	t_execcmd *cmd;

	cmd = malloc(sizeof(t_execcmd));
	ft_memset(cmd, 0, sizeof(t_execcmd *));
	cmd->type = EXEC;
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