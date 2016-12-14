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

void	ft_multi_com(char *get_line, t_env *envp, t_stack hist)
{
	char	**tmp_com;
	char	**split_com;
	int		i;

	split_com = ft_strsplit(get_line, ';');
	i = 0;
	while (split_com[i])
	{
		tmp_com = ft_strsplit(split_com[i], ' ');
		if (tmp_com)
			ft_run_commands(tmp_com, split_com[i], envp, hist);
		i++;
		freesplit(tmp_com);
	}
	if (split_com)
		freecopy(split_com);
}

void	ft_advanced_com(char **commands, char *line, t_env *envp, t_stack hist)
{
	char	*exec;
	char	**search;
	int		success;

	success = 0;
	if (ft_contains(line, ';'))
	{
		ft_multi_com(line, envp, hist);
		return ;
	}
	else if (ft_search_command((search = ft_strsplit(line, ' '))[0]) && !ft_contains(line, '>'))
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
