/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:32 by aamoussa          #+#    #+#             */
/*   Updated: 2022/08/23 14:28:29 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# define EXEC  1
# define REDIR 2
# define PIPE  3

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd {
	int		type;
	char	**argv;
	char	**eargv;
}	t_execcmd;

typedef struct s_redircmd {
	int			type;
	struct cmd	*cmd;
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
#endif