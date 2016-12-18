/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bck_i_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:30:22 by julekgwa          #+#    #+#             */
/*   Updated: 2016/09/05 07:30:34 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_full_word(char **list, char *cmd, int i)
{
	while (list[i])
	{
		if (strstr(list[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

void	ft_search_hist(char *cmd, t_stack hist, t_search *bck_search, int found)
{
	char	**l;
	int		i;
	int		n;

	if (ft_strequ(cmd, ""))
		return ;
	l = hist.list;
	n = ft_strlen(cmd);
	while (n && found)
	{
		i = -1;
		while (l[++i])
		{
			if (STRSTR(l[i], SUB(cmd, 0, n)) && !FULL(l, SUB(cmd, 0, n), i + 1))
			{
				if (ft_strlen(cmd) > ft_strlen(ft_strsub(cmd, 0, n)))
					bck_search->fail = 1;
				bck_search->prev_match = bck_search->results;
				bck_search->results = l[i];
				found = 0;
				break ;
			}
		}
		n--;
	}
}

void	ft_bck_i_search(char *cmd, int pos, t_stack *hist)
{
	char	*search;

	ft_putstr("\33[2K\r");
	ft_putstr("\33[A\r");
	ft_putstr("\33[2K\r");
	hist->search->results = "";
	hist->search->prev_match = "";
	hist->search->fail = 0;
	ft_search_hist(cmd, *hist, hist->search, 1);
	search = hist->search->results;
	ft_putstr("\n");
	ft_display_bck_i_search(cmd, pos, hist, search);
}

void	ft_display_cmd(char *cmd, int pos)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (i == pos - 1)
		{
			tputs(tgetstr("so", NULL), 1, ft_myputchar);
			ft_putchar(cmd[i]);
			tputs(tgetstr("se", NULL), 1, ft_myputchar);
		}
		else
			ft_putchar(cmd[i]);
		i++;
	}
}
