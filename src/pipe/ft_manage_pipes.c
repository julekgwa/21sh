/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:35:02 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:35:05 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_child_proc(int in[], int out, char **cmd, char **envp)
{
	pid_t	pid;
	
	if ((pid = fork()) == 0)
	{
		if (in[0] != 0)
		{
			dup2(in[0], 0);
			close(in[0]);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		if (ft_is_redirect(cmd))
			ft_file_redirection(cmd, envp, in);
		else
			execve(cmd[0], &cmd[0], envp);
	}
}

int		fork_pipes(int n[], char **cmd, char **envp, int i)
{
	int		in[2];
	int		fd[2];
	char	**cmd_s;

	in[0] = 0;
	in[1] = n[1];
	while (i < n[0] - 1)
	{
		pipe(fd);
		cmd_s = ft_strsplit(cmd[i], ' ');
		if (!ft_is_execute(cmd_s[0]))
			cmd_s[0] = ft_build_exec(envp, cmd_s);
		ft_execute_child_proc(in, fd[1], cmd_s, envp);
		close(fd[1]);
		in[0] = fd[0];
		i++;
	}
	if (in[0] != 0)
		dup2(in[0], 0);
	cmd_s = ft_strsplit(cmd[i], ' ');
	if (!ft_is_execute(cmd_s[0]))
		cmd_s[0] = ft_build_exec(envp, cmd_s);
	if (ft_is_redirect(cmd_s))
		return (ft_file_redirection(cmd_s, envp, n));
	return (execve(cmd_s[0], &cmd_s[0], envp));
}
