/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 10:46:01 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/28 10:46:03 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_up_down(char **buf, char **comm, t_stack *hist, int *pos)
{
	if (hist->count == -1 && hist->top != -1)
		hist->count = hist->top + 1;
	if (hist->count >= 0)
	{
		ft_memset(*comm, 0, BUFF_SIZE);
		ft_strcpy(*comm, ft_keys_up_down(*buf, hist, pos));
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

void	ft_display_bck_i_search(char *cmd, int pos, t_stack *hist, char *search)
{
	if (hist->search->fail || (ft_strequ(search, "") && ft_strlen(cmd) > 0))
		ft_putstr("(failed bck-i-search)`");
	else
		ft_putstr("(bck-i-search)`");
	ft_display_cmd(cmd, pos);
	ft_putstr("':");
	if (!ft_strequ(search, ""))
		ft_putstr(search);
}
