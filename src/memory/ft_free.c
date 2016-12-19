/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:34:33 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/01 08:37:07 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freecopy(char **copy)
{
	int	i;

	i = 0;
	while (i < ft_array_len(copy))
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	freesplit(char **split)
{
	free(split[0]);
	free(split);
}

void	ft_free_str(char *str, char *join)
{
	free(str);
	free(join);
}
