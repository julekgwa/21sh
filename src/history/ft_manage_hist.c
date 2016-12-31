/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_hist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:30:59 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/30 12:38:42 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_hist(char **list, int len)
{
	int	sp;
	int	i;

	i = 0;
	while (i < len)
	{
		sp = ft_strlen(ft_itoa(len)) - ft_strlen(ft_itoa(i + 1));
		ft_putstr(" ");
		ft_display_sp(sp);
		ft_putstr(ft_itoa(i + 1));
		ft_putstr("  ");
		ft_putendl(list[i]);
		i++;
	}
}

void	ft_display_hist(t_stack *hist, char **history, int lim)
{
	char	**list;

	list = hist->list;
	if (history[1] != NULL && !ft_strequ(history[1], "-c"))
	{
		lim = ft_atoi(history[1]);
		ft_print_hist(list, lim);
	}
	else if (ft_array_len(history) >= 2 && ft_strequ(history[1], "-c"))
		ft_clear_hist(hist);
	else
		ft_print_hist(list, ft_array_len(list));
}

void	ft_clear_hist(t_stack *hist)
{
	ft_memset(hist->list, 0, sizeof(hist->list));
	hist->count = -1;
	hist->top = -1;
}

char	*ft_search_replace(t_search_hist s, int i, int j, int k)
{
	s.replace = ft_memalloc(ft_strlen(s.haystack) + (ft_strlen(s.with)) + 1);
	while (s.haystack[i])
	{
		if (s.haystack[i] == s.needle[0])
		{
			if (!ft_strncmp(s.haystack + i, s.needle, ft_strlen(s.needle)))
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
	char			*search_str;
	t_search_hist	search;
	int				i;

	split = ft_strsplit(*cmd + 1, '^');
	i = *pos;
	search.haystack = ft_get_prev_hist(hist);
	search.needle = split[0];
	search.with = split[1] ? split[1] : "";
	ft_memset(*cmd, 0, BUFF_SIZE);
	search_str = ft_search_replace(search, 0, 0, 0);
	ft_strcpy(*cmd, search_str);
	if (ft_strequ(search.haystack, *cmd))
	{
		ft_putendl("\n21sh: substitution failed");
		ft_memset(*cmd, 0, BUFF_SIZE);
		ft_strcpy(*cmd, "");
	}
	i = ft_strlen(*cmd);
	ft_cursor(*cmd, i + 1, &hist);
	*pos = i;
	freecopy(split);
	free(search_str);
}
