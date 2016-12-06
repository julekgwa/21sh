/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:35:34 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:35:42 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_contains(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_multi_com(char **split_com, char *line, t_env *envp, t_stack hist)
{
	char	**tmp_com;

	while (*split_com)
	{
		tmp_com = ft_strsplit(*split_com, ' ');
		if (tmp_com)
		{
			if (ft_search_command(tmp_com[0]))
				ft_execute_commands(tmp_com, *split_com, envp, hist);
			else if (ft_build_exec(envp->list, tmp_com))
				ft_execute(ft_build_exec(envp->list, tmp_com), tmp_com, line, envp->list);
			else if (ft_is_execute(tmp_com[0]))
				ft_execute(tmp_com[0], tmp_com, line, envp->list);
			else
				ft_print_error(tmp_com[0], 0);
		}
		freecopy(tmp_com);
		split_com++;
	}
}

void	ft_advanced_com(char **commands, char *line, t_env *envp, t_stack hist)
{
	char	**split_com;
	char	*exec;
	char	**search;
	int		success;

	success = 0;
	if (ft_contains(line, ';'))
	{
		split_com = ft_strsplit(line, ';');
		ft_multi_com(split_com, line, envp, hist);
	}
	else if (ft_search_command((search = ft_strsplit(line, ' '))[0]))
	{
		success = 1;
		ft_execute_commands(search, line, envp, hist);
	}
	else if ((exec = ft_build_exec(envp->list, commands)))
	{
		ft_execute(exec, commands, line, envp->list);
		free(exec);
	}
	else if (ft_is_execute(commands[0]))
		ft_execute(commands[0], commands, line, envp->list);
	else
		ft_print_error(commands[0], 0);
	if (!success)
		freecopy(search);
}

char	*ft_last_word(const char *s)
{
	int		i;
	char	*last;
	int		j;

	i = 0;
	j = 0;
	last = (char *)malloc(sizeof(char) * ft_strlen(s));
	while (s[i])
		i++;
	i -= 1;
	while (s[i] == ' ' || s[i] == '\t')
		i--;
	while ((s[i] != ' ' && s[i] != '\t') && i >= 0)
		i--;
	i += 1;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		last[j] = s[i];
		i++;
		j++;
	}
	return (last);
}

char	*ft_first_word(const char *s)
{
	int		i;
	char	*first;
	int		j;

	i = 0;
	j = 0;
	first = (char *)malloc(sizeof(char) * ft_strlen(s));
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		first[j] = s[i];
		i++;
		j++;
	}
	return (first);
}
