/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 15:30:08 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/06 13:26:42 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int			ft_pad_zeros(int len, char *flags, int num)
{
	char	chr;
	int		l_print;

	chr = '0';
	l_print = len;
	if (ft_flags(' ', flags))
		chr = ' ';
	if (num < 0 && chr == '0')
	{
		ft_putchar('-');
		num = ft_neg_to_pos(num);
	}
	while (len-- > 0)
		ft_putchar(chr);
	len = l_print;
	ft_putnbr(num);
	return (len);
}

static unsigned int	ft_find_prec(char *flags)
{
	int	prec;

	prec = 0;
	while (*flags)
	{
		if (*flags == '.' || *flags == '0')
			prec = ft_atoi(flags + 1);
		flags++;
	}
	return (prec);
}

static int			ft_justfy(char *flags, char type, int d_i)
{
	int			width;
	int			force_pos;
	unsigned	num_digits;
	unsigned	prec;
	int			total;

	width = 0;
	force_pos = ft_flags('+', flags);
	num_digits = ft_num_digits(d_i);
	prec = ft_find_prec(flags);
	if (ft_flags('0', flags) && ft_flags('+', flags))
		prec -= 1;
	width = ft_find_width(flags);
	width -= prec;
	if (prec == 0)
		width -= num_digits;
	if (force_pos)
		width -= 1;
	total = num_digits + width;
	if (force_pos && d_i > 0 && (type == 'd' || type == 'i'))
		ft_putchar('+');
	total += ft_pad_zeros(prec - num_digits, flags, d_i);
	ft_manage_width(width);
	return (total);
}

static int			ft_no_justfy(char *flags, char type, int d_i)
{
	int			width;
	int			force_pos;
	unsigned	num_digits;
	unsigned	prec;
	int			total;

	width = 0;
	force_pos = ft_flags('+', flags);
	num_digits = ft_num_digits(d_i);
	prec = ft_find_prec(flags);
	if (ft_flags('0', flags) && ft_flags('+', flags))
		prec -= 1;
	width = ft_find_width(flags);
	width -= prec;
	if (prec == 0)
		width -= num_digits;
	if (force_pos || (d_i >= 0 && d_i < 10))
		width -= 1;
	ft_manage_width(width);
	total = width + num_digits;
	if (force_pos && d_i > 0 && (type == 'd' || type == 'i'))
		ft_putchar('+');
	total += ft_pad_zeros(prec - num_digits, flags, d_i);
	return (total);
}

int					ft_handle_d_i(char *flags, char type, const int d_i)
{
	int	l_justfy;

	l_justfy = ft_flags('-', flags);
	if (l_justfy)
		return (ft_justfy(flags, type, d_i));
	return (ft_no_justfy(flags, type, d_i));
}
