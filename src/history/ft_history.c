/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:37:50 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:38:06 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_up(t_stack *stack)
{
	if (stack->count == 0)
		return (stack->list[0]);
	return (stack->list[--stack->count]);
}

char	*ft_down(t_stack *stack)
{
	if (stack->count >= stack->top)
	{
		stack->count = stack->top + 1;
		return ("");
	}
	if (stack->count <= stack->top)
		return (stack->list[++stack->count]);
	stack->count = stack->top + 1;
	return ("");
}

int		ft_up_down(char *key_pressed)
{
	char	*key;

	key = key_pressed + 1;
	if (ft_strequ(key, "[A") || ft_strequ(key, "[5~"))
		return (1);
	else if (ft_strequ(key, "[B") || ft_strequ(key, "[6~"))
		return (1);
	return (0);
}

char	*ft_keys_up_down(char *key_pressed, t_stack *hist, int *pos)
{
	char	*key;
	char	*res;

	key = key_pressed + 1;
	res = NULL;
	if (ft_strequ(key, "[A") || ft_strequ(key, "[5~"))
	{
		if (hist->count >= 0)
			res = ft_up(hist);
		if (hist->count < 0)
			hist->count = 0;
	}
	else if (ft_strequ(key, "[B") || ft_strequ(key, "[6~"))
	{
		if (hist->count <= hist->top)
			res = ft_down(hist);
	}
	if (res != NULL)
		*pos = (int)ft_strlen(res);
	return (res);
}
