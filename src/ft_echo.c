/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 09:50:53 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/10 09:57:23 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_array_len(char **arr)
{
	int	count;

	count = 0;
	while (*arr)
	{
		count++;
		arr++;
	}
	return (count);
}

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
		if (!ft_start_with(split[1], '-'))
		{
			split++;
			while (*split)
			{
				if (ft_start_with(*split, '$'))
					ft_putstr_char(ft_rm_quotes(ft_get_env(*split, envp)), ' ');
				else
					ft_putstr_char(ft_rm_quotes(*split), ' ');
				split++;
			}
			ft_putchar('\n');
		}
	}
}
