/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 10:45:21 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 10:09:56 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(void)
{
	int	i;

	i = 0;
	while (++i < 32)
		if (i == SIGINT || i == SIGTSTP || i == SIGCHLD)
			signal(i, ft_signalhandle);
}

void	ft_signalhandle(int num)
{
	static int		i;

	i = 0;
	if (num == SIGCHLD)
		i++;
	else if (num == SIGINT && i == 1)
	{
		signal(num, SIG_DFL);
		ft_putendl("working");
		ft_putnbr(i);
		ft_putchar('\n');
		i--;
	}
	else if (num == SIGTSTP && i == 1)
	{
		signal(num, SIG_DFL);
		ft_putendl("working");
		ft_putnbr(i);
		ft_putchar('\n');
		i--;
	}
}

char	*ft_get_current_dir(void)
{
	char	*cwd;
	int		i;
	char	*home;
	char	*dir;

	cwd = NULL;
	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	dir = ft_memalloc(ft_strlen(cwd) + 1);
	ft_memset(dir, 0, ft_strlen(cwd) + 1);
	if (ft_strequ(cwd, home))
		ft_strcpy(cwd, "~");
	i = ft_strlen(cwd);
	while (i)
	{
		if (cwd[i--] == '/')
		{
			i += 2;
			break ;
		}
	}
	ft_strcpy(dir, cwd + i);
	free(cwd);
	return (dir);
}

void	ft_cmd_prompt(void)
{
	char	hostname[128];
	char	*user;
	char	*dir;

	gethostname(hostname, sizeof(hostname));
	dir = ft_get_current_dir();
	user = getenv("USER");
	ft_putstr("\33[2K\r");
	ft_putstr(GRN);
	ft_putstr("[");
	ft_putstr(user);
	ft_putstr("@");
	ft_putstr(hostname);
	ft_putstr(RESET);
	ft_putstr(" ");
	ft_putstr(CYN);
	ft_putstr(dir);
	ft_putstr(RESET);
	ft_putstr(GRN);
	ft_putstr("]$ ");
	ft_putstr(RESET);
	free(dir);
}

int		ft_enter_key(char **comm, int *pos, t_stack *hist)
{
	*pos = -1;
	if (*comm[0] == '!')
		ft_exclamation(comm, hist, pos);
	else if (*comm[0] == '^')
		ft_man_search_replace(comm, pos, *hist);
	else if (ft_end_with(*comm, ')') && !ft_start_with(*comm, '('))
	{
		ft_putendl("\n42sh: parse error near `)'");
		ft_memset(*comm, 0, ft_strlen(*comm));
		ft_strcpy(*comm, "");
		*pos = ft_strlen(*comm);
		ft_cursor(*comm, *pos + 1, hist);
	}
	else
	{
		ft_cursor(*comm, *pos, hist);
		if (hist->ctrl_r == 1)
		{
			*comm = hist->search->results;
			hist->ctrl_r = 0;
		}
		return (1);
	}
	return (0);
}
