/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_hist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:30:59 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/19 12:49:45 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_hist(char *str, int spaces, int iter)
{
	ft_putstr(" ");
	ft_display_sp(ft_strlen(ft_itoa(spaces)) - ft_strlen(ft_itoa(iter + 1)));
	ft_putstr(ft_itoa(iter + 1));
	ft_putstr("  ");
	ft_putendl(str);
}

void	ft_display_hist(t_stack *hist, char **history, int i, int lim)
{
	char	**list;

	list = hist->list;
	if (history[1] != NULL && !ft_strequ(history[1], "-c"))
	{
		lim = ft_atoi(history[1]);
		while (i < lim && *list)
			ft_print_hist(*list++, lim, i++);
	}
	else if (ft_array_len(history) >= 2 && ft_strequ(history[1], "-c"))
		ft_clear_hist(hist);
	else
	{
		while (*list != NULL)
		{
			lim = ft_strlen(ft_itoa(hist->top));
			if (!ft_strequ(*list, ""))
			{
				ft_print_hist(*list, lim - ft_strlen(ft_itoa(i + 1)), i);
				i++;
			}
			list++;
		}
	}
}

void	ft_clear_hist(t_stack *hist)
{
	int	i;

	i = 0;
	while (hist->list[i])
	{
		ft_memset(hist->list[i], '\0', ft_strlen(hist->list[i]));
		i++;
	}
	hist->count = 0;
	hist->top = 0;
}

char	*ft_search_replace(t_search_hist s, int i, int j, int k)
{
	s.replace = ft_memalloc(ft_strlen(s.haystack) + (ft_strlen(s.with)) + 1);
	while (s.haystack[i])
	{
		if (s.haystack[i] == s.needle[0])
		{
			if (!ft_strncmp(s.haystack + i, s.needle, ft_strlen(s.needle) - 1))
			{
				j = 0;
				while (s.with[j])
					s.replace[k++] = s.with[j++];
				i = ft_strlen(s.needle) + i;
				while (s.haystack[i])
					s.replace[k++] = s.haystack[i++];
				s.replace[k] = '\0';
				return (s.replace);
			}
			else
				s.replace[k++] = s.haystack[i++];
		}
		else
			s.replace[k++] = s.haystack[i++];
	}
	s.replace[k] = '\0';
	return (s.replace);
}

void	ft_man_search_replace(char **cmd, int *pos, t_stack hist)
{
	char			**split;
	t_search_hist	search;
	int				i;

	split = ft_strsplit(*cmd + 1, '^');
	i = *pos;
	search.haystack = ft_get_prev_hist(hist);
	search.needle = split[0];
	search.with = split[1];
	*cmd = ft_search_replace(search, 0, 0, 0);
	if (ft_strequ(search.haystack, *cmd))
	{
		ft_putendl("\n21sh: substitution failed");
		*cmd = "";
	}
	i = ft_strlen(*cmd);
	ft_cursor(*cmd, i + 1, &hist);
	*pos = i;
}
