/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 10:07:07 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/10 15:32:16 by ktshikot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(const char *env, char **env_list)
{
	env += 1;
	while (*env_list)
	{
		if (ft_strncmp(env, *env_list, ft_strlen(env) - 1) == 0)
			return (*env_list + ft_strlen(env) + 1);
		env_list++;
	}
	return (NULL);
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

char	*ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

void	ft_unsetting_env(char *names, char **envp)
{
	char	**variables;
	int		len;

	variables = ft_strsplit(names, ' ');
	len = ft_array_len(variables);
	if (len == 1)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		variables++;
		while (*variables)
		{
			ft_unsetenv(*variables, envp);
			variables++;
		}
	}
}
