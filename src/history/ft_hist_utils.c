/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:37:50 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:38:03 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_up_down(char **buf, char **comm, t_stack *hist, int *pos)
{
	if (hist->count == -1 && hist->top != -1)
		hist->count = hist->top + 1;
	if (hist->count >= 0)
	{
		if ((*comm = ft_keys_up_down(*buf, hist, pos)) != NULL)
			ft_cursor(*comm, ft_strlen(*comm) + 1, hist);
	}
}

void	ft_display_sp(int sp)
{
	int	i;

	i = 0;
	while (i < sp)
	{
		ft_putchar(' ');
		i++;
	}
}

char	*ft_get_prev_hist(t_stack hist)
{
	char	*prev;
	int		i;

	i = 0;
	prev = "";
	while (hist.list[i])
	{
		prev = hist.list[i];
		i++;
	}
	return (prev);
}

void	ft_ctrl_l(char *comm, int pos, t_stack *hist)
{
	ft_clear_screen();
	ft_cursor(comm, pos + 1, hist);
}
