/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bck_i_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:30:22 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/30 06:57:23 by julekgwa         ###   ########.fr       */
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
	int		i;
	char	*sub_s;

	if (ft_strequ(cmd, ""))
		return ;
	hist.counter = ft_strlen(cmd) + 1;
	while (--hist.counter && found)
	{
		i = -1;
		while (hist.list[++i])
		{
			sub_s = SUB(cmd, 0, hist.counter);
			if (STRSTR(hist.list[i], sub_s) && !FULL(hist.list, sub_s, i + 1))
			{
				if (ft_strlen(cmd) > ft_strlen(sub_s))
					bck_search->fail = 1;
				bck_search->prev_match = bck_search->results;
				bck_search->results = hist.list[i];
				found = 0;
				free(sub_s);
				break ;
			}
			free(sub_s);
		}
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
	ft_cmd_prompt();
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

void	ft_exclamation(char **comm, t_stack *hist, int *pos)
{
	char	*tmp;
	char	cmd[BUFF_SIZE];
	int		i;

	tmp = NULL;
	i = 0;
	ft_memset(cmd, 0, BUFF_SIZE);
	ft_strcpy(cmd, *comm);
	ft_memset(*comm, 0, BUFF_SIZE);
	if (ft_strequ(cmd, "!!") || ft_strequ(cmd, "!-1"))
		ft_strcpy(*comm, ft_get_prev_hist(*hist));
	else
		ft_strcpy(*comm, ft_get_hist(cmd, *hist, tmp, i));
	*pos = ft_strlen(*comm);
	ft_cursor(*comm, *pos + 1, hist);
}
