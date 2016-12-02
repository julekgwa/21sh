/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 10:41:55 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/10 10:42:02 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getchar(const int fd)
{
	static char	buff[GET_C_BUFF_SIZE];
	static char	*chr;
	static int	pos = 0;
	static int	ret = 0;

	if (pos >= ret)
	{
		if ((ret = read(fd, buff, GET_C_BUFF_SIZE)) > 0)
		{
			chr = buff;
			pos = 0;
			return (*(chr + pos++));
		}
		else
		{
			return (0);
		}
	}
	else
	{
		return (*(chr + pos++));
	}
}
