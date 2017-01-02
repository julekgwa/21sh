/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 07:48:45 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/02 15:02:50 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rm_quotes(char *cmd)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(cmd);
	while (j < len)
	{
		if (cmd[j] == 39 || cmd[j] == 34)
			j++;
		cmd[i] = cmd[j];
		i++;
		j++;
	}
	return (cmd);
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
