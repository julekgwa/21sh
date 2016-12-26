/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:35:34 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:35:52 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rm_quotes(char *s)
{
	int	slen;

	if (ft_start_with(s, '"'))
		s += 1;
	slen = ft_strlen(s);
	if (ft_end_with(s, '"'))
		s[slen - 1] = '\0';
	return (s);
}

int		ft_start_with(char *str, char c)
{
	if (str && str[0] == c)
		return (1);
	return (0);
}

int		ft_end_with(char *str, char c)
{
	if (ft_strequ(str, ""))
		return (0);
	if (str && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

void	ft_print_env(t_env *stack)
{
	int i;

	i = 0;
	while (i <= stack->top)
	{
		if (stack->list[i])
			ft_putendl(stack->list[i]);
		i++;
	}
}

char	**ft_check_env(char **cmd, char **envp)
{
	int		count;
	int		i;

	i = 0;
	count = ft_array_len(cmd);
	while (i < count)
	{
		if (ft_start_with(cmd[i], '$'))
			cmd[i] = ft_get_env(cmd[i], envp);
		i++;
	}
	return (cmd);
}
