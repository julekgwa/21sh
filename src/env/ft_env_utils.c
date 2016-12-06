#include "minishell.h"

int ft_is_full(t_env *stack)
{
	return (stack->top == stack->capacity - 1);
}

int  ft_push_env(t_env *stack, char *value)
{
	if (ft_is_full(stack))
		return (0);
	stack->list[++stack->top] = value;
	return (1);
}

t_env *copy_envp(int capacity, char **envp)
{
	int		i;
	t_env	*stack;

	stack = (t_env *)malloc(sizeof(t_env));
	i = 0;
	if (stack)
	{
		stack->capacity = capacity;
	stack->top = -1;
	stack->list = (char **)malloc(stack->capacity * sizeof(char *));
	memset(stack->list, 0, stack->capacity * sizeof(char *));
	while (envp[i])
		ft_push_env(stack, envp[i++]);
	}
	return stack;
}

void free_envp(t_env *stack)
{
	free(stack->list);
	free(stack);
}