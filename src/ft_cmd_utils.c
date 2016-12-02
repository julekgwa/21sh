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

void	ft_builtins(char **user_comm, char *get_line, char **envp, char **sp)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		ft_putendl("error while forking");
	else if (pid == 0)
		ft_execute_commands(user_comm, get_line, envp);
	if (pid > 0)
	{
		wait(NULL);
		freecopy(sp);
		exit(0);
	}
}

void	prompt(char **commands)
{
	ft_putstr(GRN);
	ft_putstr("$> ");
	ft_putstr(RESET);
	get_next_line(0, commands);
}

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
