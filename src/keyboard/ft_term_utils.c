/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:52:55 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/27 15:31:53 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_myputchar(int c)
{
	return (write(2, &c, 1));
}

void	ft_create_stack(t_stack *stack, char **envp)
{
	t_search	*search;
	char		*path;
	char		**split;

	search = (t_search *)malloc(sizeof(t_search) + 1);
	ft_memset(stack->list, 0, 4096);
	ft_memset(&stack->hash, 0, sizeof(t_hash *) * MAX_HASH);
	path = ft_get_env("$PATH", envp);
	split = ft_strsplit(path, ':');
	ft_hash_table_bin(stack->hash, split);
	search->results = "";
	search->prev_match = "";
	search->fail = 0;
	stack->search = search;
	stack->ctrl_r = 0;
	stack->count = -1;
	stack->success = 0;
	stack->envp = envp;
	stack->paste = "";
	stack->top = -1;
	stack->capacity = 4096;
}

void	ft_push(t_stack *stack, char *hist)
{
	if (stack->top == stack->capacity - 1)
		return ;
	stack->list[++stack->top] = hist;
	stack->count = stack->top + 1;
}

void	ft_exclamation(char **comm, t_stack *hist, int *pos)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (ft_strequ(*comm, "!!") || ft_strequ(*comm, "!-1"))
		*comm = ft_get_prev_hist(*hist);
	else
		*comm = ft_get_hist(*comm, *hist, tmp, i);
	*pos = ft_strlen(*comm);
	ft_cursor(*comm, *pos + 1, hist);
}

char	*ft_get_hist(char *history, t_stack hist, char *tmp, int i)
{
	char	*com;
	int		index;

	tmp = history + 1;
	i = -1;
	com = "";
	if ((index = ft_atoi(tmp)))
	{
		index -= 1;
		while (hist.list[++i] && i != index)
			if (i == index)
				com = hist.list[i];
	}
	else
	{
		while (hist.list[++i])
			if (ft_strncmp(tmp, hist.list[i], ft_strlen(tmp)) == 0)
				com = hist.list[i];
	}
	if (ft_strequ(com, ""))
	{
		ft_print_error(tmp, 5);
		return (strdup(com));
	}
	return (com);
}
