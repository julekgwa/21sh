/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:17:00 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:17:19 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_find_width(char *flags)
{
	int	width;
	int	found;

	width = 0;
	found = 0;
	while (*flags != '.' && found == 0)
	{
		if (*flags >= 48 && *flags <= 57)
		{
			width = ft_atoi(flags);
			found = 1;
		}
		flags++;
	}
	return (width);
}
