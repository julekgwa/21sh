/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:37:20 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/02 13:20:30 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_is_executable(const char *path)
{
    struct stat path_stat;

    ft_memset(&path_stat, 0, sizeof(struct stat));
    if (stat(path, &path_stat) == 0 && path_stat.st_mode & S_IXUSR)
        return (1);
    return (0);
}

int     ft_is_dir(const char *path)
{
    struct stat path_stat;

    ft_memset(&path_stat, 0, sizeof(struct stat));
    if (stat(path, &path_stat) < 0)
        return (0);
    return S_ISDIR(path_stat.st_mode);
}

void    ft_rm_quotes_array(char *av[], char **cmd, char *com)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        av[i] = ft_rm_quotes(cmd[i]);
        i++;
    }
    if (EQUAL(com, "/bin/ls") || EQUAL(com, "/usr/bin/ls"))
        av[i++] = "--color=auto";
    else if (EQUAL(com, "/bin/grep") || EQUAL(com, "/usr/bin/grep"))
        av[i++] = "--color=auto";
    av[i] = 0;
}

int ft_execute_cmd(char *com, char **cmd, char **envp)
{
    int exec;
    char    *av[BUFF_SIZE];

    ft_memset(av, 0, sizeof(char *) * BUFF_SIZE);
    ft_rm_quotes_array(av, cmd, com);
    exec = execve(com, &av[0], envp);
    if (exec == -1 && !ft_is_executable(com))
        ft_print_error(com, 1);
    else if (exec == -1 && ft_is_dir(com))
        ft_print_error(com, 2);
    return (exec);
}
