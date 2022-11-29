/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:23:37 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/11/03 07:06:02 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork process");
		exit(1);
	}
	return (pid);
}

void	free_args_list(t_list **args)
{
	t_list	*arg;

	while ((*args))
	{
		ft_free(&((*args)->content));
		arg = (*args);
		(*args) = (*args)->next;
		free(arg);
	}
}

void	free_all(t_cmd *cmd)
{
	t_pipecmd	*pipcmd;
	t_execcmd	*execcmd;
	int			i;

	i = 0;
	if (cmd->type == PIPE)
	{
		pipcmd = (t_pipecmd *)(cmd);
		free_all(pipcmd->left);
		free_all(pipcmd->right);
		free(pipcmd);
	}
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)(cmd);
		while (execcmd->argument && execcmd->argument[i])
			ft_free(&execcmd->argument[i++]);
		free_args_list(&(execcmd->args));
		free(execcmd->argument);
		free(execcmd);
	}
}

void	free_cmd(t_cmd *cmd)
{
	free_all(cmd);
}
