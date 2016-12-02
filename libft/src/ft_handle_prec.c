/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_prec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:17:37 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:22:23 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	ft_prec(char *flags)
{
	int	prec;

	prec = 0;
	while (*flags)
	{
		if (*flags == '.')
			prec = ft_atoi(flags + 1);
		flags++;
	}
	return (prec);
}

void		ft_handle_prec(char *flags, int digits)
{
	int	prec;
	int	i;
	int	total;

	prec = 0;
	total = 0;
	i = 0;
	if (ft_flags('.', flags))
	{
		prec = ft_prec(flags);
		total = prec - digits;
		while (i < total)
		{
			ft_putchar('0');
			i++;
		}
	}
}
