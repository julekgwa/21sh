/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 07:45:41 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/29 07:45:44 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_specila_char(char c)
{
	if (c == 'b')
		return ('\b');
	else if (c == 't')
		return ('\t');
	else if (c == 'n')
		return ('\n');
	else if (c == 'v')
		return ('\v');
	else if (c == 'a')
		return ('\a');
	else if (c == '\\')
		return ('\\');
	return (c);
}

void	ft_putstr_char(char *s, char c)
{
	int		i;
	char	tmp;

	i = 0;
	while (s[i])
	{
		tmp = s[i];
		if (s[i] == '\\')
		{
			tmp = ft_specila_char(s[i + 1]);
			i++;
		}
		ft_putchar(tmp);
		i++;
	}
	ft_putchar(c);
}

int		ft_check_options(char opt, const char *options)
{
	while (*options)
	{
		if (*options == opt)
			return (1);
		options++;
	}
	return (0);
}

void	ft_environ_value(char *env, char **envp)
{
	char	*tmp;

	if (ft_start_with(env, '$'))
	{
		tmp = ft_get_env(env, envp);
		if (tmp)
			ft_putstr_char(QUOTES(tmp), ' ');
	}
	else
		ft_putstr_char(QUOTES(env), ' ');
}

void	ft_echo(char *echo, char **envp)
{
	char	**split;
	int		count;

	split = ft_strsplit(echo, ' ');
	count = ft_array_len(split);
	if (count == 0)
		ft_putchar('\n');
	else
	{
		count = 0;
		if (!ft_start_with(split[1], '-'))
		{
			count++;
			while (split[count])
				ft_environ_value(split[count++], envp);
			ft_putchar('\n');
		}
	}
	freecopy(split);
}
