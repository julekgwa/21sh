/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 09:07:29 by goisetsi          #+#    #+#             */
/*   Updated: 2016/12/01 08:45:06 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**getpath(char **envp)
{
	int		i;
	char	**s1;
	char	**s2;

	i = 0;
	while (envp[i])
	{
		s1 = ft_strsplit(envp[i], '=');
		if (ft_strequ(s1[0], "PATH"))
		{
			s2 = ft_strsplit(s1[1], ':');
			freecopy(s1);
			return (s2);
		}
		i++;
		freecopy(s1);
	}
	return (NULL);
}

int		ft_is_execute(char *command)
{
	if (access(command, F_OK) == 0)
		return (1);
	return (0);
}

char	*ft_more(char **envp, char **split)
{
	char	**new;
	char	*str;
	int		i;
	char	*join;

	i = 0;
	new = getpath(envp);
	if (new == NULL)
		return (NULL);
	while (new[i] != '\0')
	{
		join = ft_strjoin(new[i], "/");
		str = ft_strjoin(join, split[0]);
		if (access(str, F_OK) == 0)
		{
			free(join);
			freecopy(new);
			return (str);
		}
		i++;
		ft_free_str(str, join);
	}
	freecopy(new);
	return (NULL);
}

void	ft_execute_bin(char **command, char **envp)
{
	pid_t	pid;
	int		exec;

	pid = fork();
	if (pid == 0)
	{
		exec = execve(command[0], &command[0], envp);
		if (exec == -1)
		{
			ft_print_error(command[0], 1);
			exit(0);
		}
	}
	if (pid > 0)
		wait(NULL);
}

void	ft_execute(char **envp, char **sp)
{
	pid_t	pid;
	char	*cmd;
	int		exec;

	cmd = ft_more(envp, sp);
	pid = fork();
	if (pid == 0)
	{
		exec = execve(cmd, &sp[0], envp);
		if (exec == -1)
		{
			ft_print_error(cmd, 1);
			exit(0);
		}
	}
	if (pid > 0)
	{
		wait(NULL);
		free(cmd);
	}
}
