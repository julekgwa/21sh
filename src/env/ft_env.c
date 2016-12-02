/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 10:23:21 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/01 08:42:03 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_putenv(char *str, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	envp[i] = malloc(strlen(str));
	if (envp[i])
	{
		envp[i] = ft_strdup(str);
		envp[++i] = 0;
		return (1);
	}
	return (0);
}

int		ft_setenv(const char *name, const char *val, int ovride, char **envp)
{
	char	*es;
	int		i;

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
	i = (ft_putenv(es, envp) != 0) ? -1 : 0;
	free(es);
	return (i);
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

char	*ft_get_str(char **av)
{
	char	*ps;
	int		i;
	int		j;
	int		found;

	ps = av[2];
	i = 2;
	j = 3;
	found = 0;
	if (ft_start_with(av[2], '"'))
	{
		while (!ft_end_with(av[i], '"') && av[i])
			i++;
		if (ft_end_with(av[i], '"'))
			found = 1;
		while (j <= i && found)
		{
			ps = ft_strjoin(ps, " ");
			ps = ft_strjoin(ps, av[j]);
			j++;
		}
	}
	return (ps);
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
