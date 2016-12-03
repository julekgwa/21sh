/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:31:50 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:31:52 by goisetsi         ###   ########.fr       */
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
