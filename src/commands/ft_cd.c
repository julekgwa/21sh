/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 07:44:27 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/29 07:44:29 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_space(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

char	*ft_remove_qoutes(char *s)
{
	int	slen;

	if (!ft_start_with(s, '"') || !ft_end_with(s, '"'))
		return (s);
	if (*s == '"')
		s += 1;
	slen = ft_strlen(s);
	if (s[slen - 1] == '"')
		s[slen - 1] = '\0';
	return (s);
}

char	*ft_clean_str(char *s)
{
	char	*clean;
	int		i;
	int		j;

	if (!ft_start_with(s, '"') && !ft_end_with(s, '"'))
		return (s);
	clean = ft_memalloc(ft_strlen(s) + ft_count_space(s));
	i = 0;
	j = 0;
	if (clean)
	{
		while (s[i])
		{
			if (s[i] == ' ')
			{
				clean[j] = '\\';
				j++;
			}
			clean[j] = s[i];
			i++;
			j++;
		}
		s = clean;
	}
	return (s);
}

void	ft_modpwd(int f, char *oldpwd, t_env *envp)
{
	char	*current;

	if (f != -1)
	{
		current = getcwd(NULL, 0);
		ft_setenv("OLDPWD", oldpwd, 1, envp);
		ft_setenv("PWD", current, 1, envp);
		free(current);
	}
	free(oldpwd);
}

void	ft_cd(char **directory, t_env *envp)
{
	char	*dir;
	char	*oldpwd;
	int		dirflag;

	dirflag = 0;
	oldpwd = getcwd(NULL, 0);
	dir = directory[1];
	if (dir == NULL || (ft_strequ(dir, "~") && ft_strlen(dir) == 1))
		dirflag = chdir(ft_get_env("$HOME", envp->list));
	else if (ft_start_with(dir, '~'))
		dirflag = ft_user_dir(dir, envp->list);
	else if (ft_strequ(dir, "-"))
		dirflag = chdir(ft_get_env("$OLDPWD", envp->list));
	else
	{
		dir = ft_clean_str(dir);
		dir = ft_remove_qoutes(dir);
		if ((dirflag = chdir(dir) == -1))
		{
			ft_print_error(dir, 3);
			return ;
		}
	}
	ft_modpwd(dirflag, oldpwd, envp);
}
