/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:28:27 by zoukaddo          #+#    #+#             */
/*   Updated: 2022/09/15 17:21:53 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <string.h>


int cd (char **av, char **envp,int ac)
{
    char *path;
    char *oldpwd;
    char *pwd;
    char *tmp;
    int i;

    i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], "PWD=" , 4) == 0)
            pwd = envp[i];
        if (strncmp(envp[i], "OLDPWD=", 7) == 0)
            oldpwd = envp[i];
        i++;
    }
    if (av == NULL)
        path = getenv("HOME");
    else if (strcmp(*av, "-") == 0)
        path = oldpwd + 7;
    else if (ac > 1)
        path = av[1];
    tmp = pwd + 4;
    setenv("OLDPWD", tmp, 1);
    setenv("PWD", path, 1);
    chdir(path);
    printf("PWD = %s\n", getenv("PWD"));
    printf("OLDPWD = %s\n", getenv("OLDPWD"));
    printf("getcwd = %s\n", getcwd(NULL, 0));
    return (0);
}

int main(int ac, char **av, char **envp)
{
    cd(av,envp, ac);
    return (0);
}


