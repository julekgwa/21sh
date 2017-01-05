/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:55:16 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/04 13:29:46 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_full(t_env *stack)
{
	return (stack->top == stack->capacity - 1);
}

int		ft_push_env(t_env *stack, char *value)
{
	if (ft_is_full(stack))
		return (0);
	stack->list[++stack->top] = value;
	return (1);
}

t_env	*copy_envp(int capacity, char **envp)
{
	int		i;
	t_env	*stack;

	stack = (t_env *)malloc(sizeof(t_env));
	i = 0;
	if (stack)
	{
		stack->capacity = capacity;
		stack->top = -1;
		stack->malloc_id = -1;
		stack->list = (char **)malloc(stack->capacity * sizeof(char *));
		ft_memset(stack->list, 0, stack->capacity * sizeof(char *));
		while (envp[i])
			ft_push_env(stack, envp[i++]);
	}
	return (stack);
}

void	free_list(t_env *stack)
{
	int	i;

	i = stack->malloc_id;
	if (i < 0)
		return ;
	while (i < stack->top)
	{
		if (stack->list[i])
			free(stack->list[i]);
		i++;
	}
}

void	free_envp(t_env *stack)
{
	free_list(stack);
	free(stack->list);
	free(stack);
}
