/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:27:04 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 10:08:01 by julekgwa         ###   ########.fr       */
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
			ft_execute_cmd(cmd[0], &cmd[0], envp);
		exit(0);
	}
}

int		fork_pipes(int n[], char **cmd, char **envp, t_stack *hist)
{
	int		in[2];
	int		fd[2];
	char	**cmd_s;

	in[0] = 0;
	in[1] = n[1];
	while (hist->counter < n[0] - 1)
	{
		pipe(fd);
		cmd_s = ft_strsplit(cmd[hist->counter], ' ');
		if (!ft_is_execute(cmd_s[0]))
			cmd_s[0] = ft_build_exec(cmd_s, hist);
		ft_execute_child_proc(in, fd[1], cmd_s, envp);
		close(fd[1]);
		in[0] = fd[0];
		hist->counter++;
	}
	if (in[0] != 0)
		dup2(in[0], 0);
	cmd_s = ft_strsplit(cmd[hist->counter], ' ');
	if (!ft_is_execute(cmd_s[0]))
		cmd_s[0] = ft_build_exec(cmd_s, hist);
	if (ft_is_redirect(cmd_s))
		return (ft_file_redirection(cmd_s, envp, n));
	return (ft_execute_cmd(cmd_s[0], &cmd_s[0], envp));
}
