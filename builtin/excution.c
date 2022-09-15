/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:52 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/14 20:28:54 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void    command_excution()
{
    int ret;
    int i;
    
    i = 0;
    while(i < nbrofsimplecommand)
    {
        ret = fork();
        if (ret == 0)
        {
            if(execve())
            perror("execve");
            exit(1);
        }
        else if (ret < 0)
        {
            perror("fork");
            return ;
        }
        i++;
    }
    waitpid(ret,NULL);
}