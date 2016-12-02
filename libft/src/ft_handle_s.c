/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:02:45 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:03:21 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	ft_find_prec(char *flags, char *s)
{
	int	prec;

	prec = ft_strlen(s);
	while (*flags)
	{
		if (*flags == '.')
			prec = ft_atoi(flags + 1);
		flags++;
	}
	return (prec);
}

void		ft_handle_s(char *flags, char *s)
{
	int	l_justfy;
	int	width;
	int	prec;

	l_justfy = ft_flags('-', flags);
	prec = ft_find_prec(flags, s);
	width = ft_find_width(flags) - prec;
	if (prec > (int)ft_strlen(s))
		width = ft_find_width(flags) - ft_strlen(s);
	if (l_justfy)
	{
		ft_putnstr(s, prec);
		ft_manage_width(width);
	}
	else
	{
		ft_manage_width(width);
		ft_putnstr(s, prec);
	}
}
