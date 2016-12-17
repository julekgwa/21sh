/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:31:50 by goisetsi          #+#    #+#             */
/*   Updated: 2016/12/15 14:31:17 by julekgwa         ###   ########.fr       */
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

void	ft_someshit(void)
{
	ft_putstr("\33[2K\r");
	ft_putstr(GRN);
	ft_putstr("$> ");
	ft_putstr(RESET);
}

int		ft_enter_key(char **comm, int *pos, t_stack *hist)
{
	*pos = -1;
	ft_cursor(*comm, *pos, hist);
	return (1);
}
