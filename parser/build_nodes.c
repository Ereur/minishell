/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:43:08 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/02 04:21:41 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	ft_memset(cmd, 0, sizeof(t_execcmd *));
	cmd->type = EXEC;
	cmd->output = 1;
	cmd->input = 0;
	cmd->args = NULL;
	cmd->argument = NULL;
	return ((t_cmd *)(cmd));
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*root;

	if (!right)
	{
		free_cmd(left);
		return (NULL);
	}
	root = malloc(sizeof(t_pipecmd));
	ft_memset(root, 0, sizeof(t_pipecmd *));
	root->type = PIPE;
	root->left = left;
	root->right = right;
	return ((t_cmd *)(root));
}
