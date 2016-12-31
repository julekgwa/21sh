/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:37:20 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/31 01:56:13 by julekgwa         ###   ########.fr       */
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

int ft_execute_cmd(char *com, char **cmd, char **envp)
{
    int exec;

    exec = execve(com, &cmd[0], envp);
    if (exec == -1 && !ft_is_executable(com))
        ft_print_error(com, 1);
    else if (exec == -1 && ft_is_dir(com))
        ft_print_error(com, 2);
    return (1);
}
