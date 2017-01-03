/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 10:46:54 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/02 07:46:15 by julekgwa         ###   ########.fr       */
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
	if (EQUAL(key, "[A") || EQUAL(key, "[5~") || key_pressed[0] == 16)
		return (1);
	else if (EQUAL(key, "[B") || EQUAL(key, "[6~"))
		return (1);
	return (0);
}

char	*ft_keys_up_down(char *key_pressed, t_stack *hist, int *pos)
{
	char	*key;
	char	*res;

	key = key_pressed + 1;
	res = "";
	if (EQUAL(key, "[A") || EQUAL(key, "[5~") || key_pressed[0] == 16
		|| EQUAL(key_pressed, "5A"))
	{
		if (hist->count >= 0)
			res = ft_up(hist);
		if (hist->count < 0)
			hist->count = 0;
	}
	else if (EQUAL(key, "[B") || EQUAL(key, "[6~") || EQUAL(key_pressed, "5A"))
	{
		if (hist->count <= hist->top)
			res = ft_down(hist);
	}
	if (res != NULL)
		*pos = (int)ft_strlen(res);
	return (res);
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
	if (EQUAL(com, ""))
		ft_print_error(tmp, 5);
	return (com);
}
