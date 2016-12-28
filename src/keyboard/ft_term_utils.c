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
	freecopy(split);
}

void	ft_push(t_stack *stack, char *hist)
{
	if (stack->top == stack->capacity - 1)
		return ;
	stack->list[++stack->top] = hist;
	stack->count = stack->top + 1;
}
