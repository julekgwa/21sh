/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c_signal_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:35:34 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:35:42 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c_signal_handler(int signum)
{
	ft_putstr("\n");
	ft_cmd_prompt();
	(void)signum;
}

void	ft_print_error(char *cmd, int errorno)
{
	if (errorno == 0)
	{
		ft_putstr("21sh: ");
		ft_putstr(cmd);
		ft_putstr(": command not found...\n");
	}
	else if (errorno == 1)
	{
		ft_putstr("21sh: ");
		ft_putstr(cmd);
		ft_putstr(": Permission denied\n");
	}
	else if (errorno == 3)
	{
		ft_putstr("cd: ");
		ft_putstr("no such file or directory: ");
		ft_putendl(cmd);
	}
	else if (errorno == 5)
	{
		ft_putstr("\n21sh: event not found: ");
		ft_putendl(cmd);
		return ;
	}
}

void	prompt(t_cmd *command, t_stack *hist)
{
	char			*comm;
	char			*buf;
	int				pos;

	buf = ft_memalloc(GET_C_BUFF_SIZE);
	comm = ft_memalloc(1000);
	pos = 0;
	hist->counter = 1;
	ft_cmd_prompt();
	tputs(tgetstr("so", NULL), 1, ft_myputchar);
	ft_putchar(' ');
	tputs(tgetstr("se", NULL), 1, ft_myputchar);
	command->get_line = strdup(ft_build_comm(hist, comm, buf, pos));
	free(buf);
	free(comm);
}

char	**envp_cpy(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	copy = (char **)malloc((ft_array_len(envp) + 1) * sizeof(char *));
	copy[ft_array_len(envp)] = NULL;
	if (copy)
	{
		while (envp[i])
		{
			copy[i] = ft_strdup(envp[i]);
			i++;
		}
	}
	return (copy);
}

int		ft_array_len(char **arr)
{
	int	count;

	count = 0;
	while (*arr)
	{
		count++;
		arr++;
	}
	return (count);
}
