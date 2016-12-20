/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:46:31 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/19 12:46:36 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **cmd, t_env *envp)
{
	char	*name;
	char	**split;
	char	**r;

	if (cmd[1][0] == '=')
	{
		ft_putstr("21sh: export: `");
		ft_putstr(cmd[1]);
		ft_putendl("': not a valid identifier");
		return ;
	}
	if (cmd[1] && CONTAINS(cmd[1], '='))
	{
		split = SPLIT(cmd[1], '=');
		name = split[0];
		r = NULL;
		ft_unsetenv(name, envp, r);
		ft_push_env(envp, ft_strdup(cmd[1]));
		if (envp->malloc_id == -1)
			envp->malloc_id = envp->top;
		freecopy(split);
	}
}
