/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 07:46:27 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/29 07:46:30 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_putenv(char *str, t_env *envp)
{
	int	i;

	i = ft_push_env(envp, str);
	if (i)
	{
		if (envp->malloc_id == -1)
			envp->malloc_id = envp->top - 1;
	}
	return (i);
}

int		ft_setenv(const char *name, const char *val, int ovride, t_env *envp)
{
	char	*es;
	char	**r;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL ||
			val == NULL)
	{
		return (-1);
	}
	if (ft_get_env(name, envp->list) != NULL && ovride == 0)
		return (0);
	r = NULL;
	ft_unsetenv(name, envp, r);
	es = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(val) + 2));
	ft_memset(es, 0, sizeof(char) * (ft_strlen(name) + ft_strlen(val) + 2));
	if (es == NULL)
		return (-1);
	ft_strcpy(es, name);
	ft_strcat(es, "=");
	ft_strcat(es, val);
	return ((ft_putenv(es, envp) != 0) ? -1 : 0);
}

int		ft_unsetenv(const char *name, t_env *envp, char **r)
{
	char	**w;
	size_t	len;
	int		i;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	r = envp->list;
	w = envp->list;
	i = 0;
	len = ft_strlen(name);
	while (*r)
	{
		if (ft_strncmp(*r, name, len) != 0 || (*r)[len] != '=')
			*w++ = *r;
		else if (ft_strncmp(*r, name, len) == 0 || (*r)[len] == '=')
		{
			if (i >= envp->malloc_id && envp->malloc_id != -1)
				free(*r);
			envp->top--;
		}
		r++;
		i++;
	}
	*w = NULL;
	return (0);
}

void	ft_unsetting_env(char *names, t_env *envp, t_stack *hist)
{
	char	**variables;
	char	**r;
	int		len;
	int		i;

	variables = ft_strsplit(names, ' ');
	r = NULL;
	len = ft_array_len(variables);
	i = 1;
	if (len == 1)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		while (variables[i])
		{
			len = ft_unsetenv(variables[i], envp, r);
			if (len == 0 && ft_strequ(variables[i], "PATH"))
				ft_free_hash_table(hist->hash);
			i++;
		}
	}
	freecopy(variables);
}

void	ft_set_envir(t_env *envp, char *str, t_stack *hist)
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
		len = ft_setenv(name, value, 1, envp);
	ft_set_hash_table(len, name, envp->list, hist);
	freecopy(split);
}
