/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:32:58 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:33:09 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_myputchar(int c)
{
	return (write(2, &c, 1));
}

void		ft_clear_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_myputchar);
}

void		ft_create_stack(t_stack *stack)
{
	ft_memset(stack->list, 0, 4096);
	stack->size = 0;
	stack->hist_count = 0;
	stack->capacity = 4096;
}

void		ft_push(t_stack *stack, char *hist)
{
	if (stack->size == stack->capacity)
		return ;
	stack->list[stack->size++] = hist;
	stack->hist_count++;
}

void		ft_display_hist(t_stack hist)
{
	int		i;

	i = 0;
	while (hist.list[i])
	{
		ft_putnbr(i + 1);
		ft_putstr("  ");
		ft_putendl(hist.list[i]);
		i++;
	}
}
