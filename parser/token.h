/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:04:56 by aamoussa          #+#    #+#             */
/*   Updated: 2022/10/28 19:00:22 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "../minishell.h"

int		gettoken(char **ps, char *es, char **q, char **eq);
int		skip_and_find(char **ps, char *es, char *tok);
int		skip_and_find_0(char **ps, char *es);
void	raise_error(char *message, int exitcode, int tok);

// int	gettoken();


#endif