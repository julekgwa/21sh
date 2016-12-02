/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:01:35 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:02:19 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_manage_c(char *flags, char c)
{
	int	l_justfy;
	int	width;
	int	total;

	l_justfy = ft_flags('-', flags);
	width = ft_find_width(flags);
	total = 0;
	if (l_justfy)
	{
		ft_putchar(c);
		ft_manage_width(width - 1);
		total += width + 1;
	}
	else
	{
		ft_manage_width(width - 1);
		ft_putchar(c);
		total += width + 1;
	}
	return (total - 2);
}
