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
	stack->size--;
	if (stack->size >= 0)
		return (stack->list[stack->size]);
	else
		return (NULL);
}

char	*ft_down(t_stack *stack)
{
	stack->size++;
	if (stack->size < stack->hist_count)
		return (stack->list[stack->size]);
	else
		return (NULL);
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
		if (hist->size > 0)
		{
			res = ft_up(hist);
		}
	}
	else if (ft_strequ(key, "[B") || ft_strequ(key, "[6~"))
	{
		if (hist->size < hist->hist_count)
			res = ft_down(hist);
	}
	if (res != NULL)
		*pos = (int)ft_strlen(res);
	return (res);
}
