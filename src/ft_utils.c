/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 10:01:35 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/10 10:30:42 by julekgwa         ###   ########.fr       */
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
	if (str && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

void	ft_print_env(char **envp)
{
	char *s;

	while ((s = *envp++))
		ft_putendl(s);
}

void	ft_check_env(char ***command, char **envp)
{
	int		count;
	char	**cmd;
	int		i;

	i = 0;
	cmd = *command;
	count = ft_array_len(cmd);
	while (i < count)
	{
		if (ft_start_with(cmd[i], '$'))
			cmd[i] = ft_get_env(cmd[i], envp);
		i++;
	}
	*command = cmd;
}
