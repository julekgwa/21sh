/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:29:45 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:29:48 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_putenv(char *str, char **envp)
{
	char	**r;
	int		i;

	r = envp;
	i = 0;
	while (r[i])
	{
		i++;
	}
	r[i] = malloc(strlen(str));
	if (r[i])
	{
		r[i] = str;
		r[++i] = 0;
		return (1);
	}
	return (0);
}

int		ft_setenv(const char *name, const char *val, int ovride, char **envp)
{
	char *es;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL ||
			val == NULL)
	{
		return (-1);
	}
	if (ft_get_env(name, envp) != NULL && ovride == 0)
		return (0);
	ft_unsetenv(name, envp);
	es = ft_memalloc(ft_strlen(name) + ft_strlen(val) + 2);
	if (es == NULL)
		return (-1);
	ft_strcpy(es, name);
	ft_strcat(es, "=");
	ft_strcat(es, val);
	return ((ft_putenv(es, envp) != 0) ? -1 : 0);
}

int		ft_unsetenv(const char *name, char **envp)
{
	char	**r;
	char	**w;
	size_t	len;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	r = envp;
	w = envp;
	len = ft_strlen(name);
	while (*r)
	{
		if (ft_strncmp(*r, name, len) != 0 || (*r)[len] != '=')
			*w++ = *r;
		r++;
	}
	*w = NULL;
	return (0);
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

void	ft_set_envir(char **envp, char *str)
{
	char	*value;
	char	*name;
	char	**split;
	int		len;

	split = ft_strsplit(str, ' ');
	len = ft_array_len(split);
	if (len == 1)
	{
		ft_print_env(envp);
		return ;
	}
	name = split[1];
	value = ft_get_str(split);
	if (len > 3 && !ft_end_with(split[len - 1], '"'))
	{
		ft_putendl("setenv: Too many arguments.");
		return ;
	}
	if (ft_start_with(name, '"'))
		ft_putendl("setenv: Variable name must begin with a letter.");
	else
		ft_setenv(name, value, 1, envp);
}
