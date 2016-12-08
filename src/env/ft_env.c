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

int		ft_putenv(char *str, t_env *envp)
{
	int	i;

	i = ft_push_env(envp, ft_strdup(str));
	if (i)
	{
		free(str);
		if (envp->malloc_id == -1)
			envp->malloc_id = envp->top;
	}
	return (i);
}

int		ft_setenv(const char *name, const char *val, int ovride, t_env *envp)
{
	char	*es;
	int		i;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL ||
			val == NULL)
	{
		return (-1);
	}
	if (ft_get_env(name, envp->list) != NULL && ovride == 0)
		return (0);
	ft_unsetenv(name, envp);
	es = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(val) + 2));
	ft_memset(es, 0, ft_strlen(name) + ft_strlen(val) + 2);
	if (es == NULL)
		return (-1);
	ft_strcpy(es, name);
	ft_strcat(es, "=");
	ft_strcat(es, val);
	i = (ft_putenv(es, envp) != 0) ? -1 : 0;
	return (i);
}

int		ft_unsetenv(const char *name, t_env *envp)
{
	char	**r;
	char	**w;
	size_t	len;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	r = envp->list;
	w = envp->list;
	len = ft_strlen(name);
	while (*r)
	{
		if (ft_strncmp(*r, name, len) != 0 || (*r)[len] != '=')
			*w++ = *r;
		if (ft_strncmp(*r, name, len) == 0 || (*r)[len] == '=')
			envp->top--;
		r++;
	}
	*w = NULL;
	return (0);
}

void	ft_unsetting_env(char *names, t_env *envp)
{
	char	**variables;
	int		len;
	int		i;

	variables = ft_strsplit(names, ' ');
	len = ft_array_len(variables);
	i = 1;
	if (len == 1)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		while (variables[i])
		{
			ft_unsetenv(variables[i], envp);
			i++;
		}
	}
	freecopy(variables);
}

void	ft_set_envir(t_env *envp, char *str)
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
	freecopy(split);
}
