/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:27:08 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:27:12 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_buff(char **com, int pos, char c)
{
	char	*copy;
	char	*buffer;
	int		i;
	int		j;

	copy = *com;
	buffer = ft_memalloc(ft_strlen(copy) + 1);
	if (pos >= (int)ft_strlen(copy))
	{
		ft_memcpy(buffer, copy, ft_strlen(copy));
		buffer[pos] = c;
	}
	else
	{
		i = 0;
		j = 0;
		while (copy[i])
		{
			buffer[j] = (j == pos) ? c : copy[i++];
			j++;
		}
	}
	// free(*com);
	*com = ft_strdup(buffer);
	free(buffer);
	ft_cursor(*com, pos + 2);
}
