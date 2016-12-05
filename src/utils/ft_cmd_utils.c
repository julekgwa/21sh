/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:43 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/01 08:41:16 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, char *get_line)
{
	freecopy(cmd);
	free(get_line);
	exit(0);
}

// void	ft_builtins(char **user_comm, char *get_line, char **envp, char **sp)
// {
// 	pid_t	pid;

// 	if ((pid = fork()) < 0)
// 		ft_putendl("error while forking");
// 	else if (pid == 0)
// 		ft_execute_commands(user_comm, get_line, envp);
// 	if (pid > 0)
// 	{
// 		wait(NULL);
// 		freecopy(sp);
// 		exit(0);
// 	}
// }

int		ft_spaces_tabs(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != 32 && s[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int		ft_user_dir(char *dir, char **envp)
{
	char	*home;
	int		success;

	home = ft_strjoin(ft_get_env("$HOME", envp), dir + 1);
	success = chdir(home);
	if (success == 0)
	{
		free(home);
		return (1);
	}
	free(home);
	return (-1);
}
