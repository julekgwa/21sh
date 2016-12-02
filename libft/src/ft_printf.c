/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 07:55:33 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/06 10:29:09 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdarg.h>

int	ft_manage_flags(char *flags, char *trav, va_list arg)
{
	int	printed;

	printed = 0;
	if (*trav == 'd' || *trav == 'i')
		printed += ft_handle_d_i(flags, *trav, va_arg(arg, int));
	else if (*trav == '%')
		printed += ft_manage_c(flags, '%');
	else if (*trav == 'u' || *trav == 'U')
		ft_handle_d_i(flags, *trav, ft_atoi(ft_base(va_arg(arg, t_u_int), 10)));
	else if (*trav == 'c' || *trav == 'C')
		printed += ft_manage_c(flags, va_arg(arg, int));
	else if (*trav == 's')
		ft_handle_s(flags, va_arg(arg, char *));
	else if (*trav == 'o' || *trav == 'O')
		ft_handle_o_x(flags, *trav, ft_base(va_arg(arg, unsigned int), 8));
	else if (*trav == 'x')
		ft_handle_o_x(flags, *trav, ft_base(va_arg(arg, unsigned int), 16));
	else if (*trav == 'X')
		ft_handle_o_x(flags, *trav, ft_base(va_arg(arg, unsigned int), 16));
	else if (*trav == 'S')
		ft_putwchar_t(va_arg(arg, wchar_t *));
	else if (*trav == 'p')
		ft_strhex(ft_base(va_arg(arg, unsigned long), 16));
	return (printed);
}

int	ft_printf(char *format, ...)
{
	char	*trav;
	va_list	arg;
	int		i;
	char	*flags;

	va_start(arg, format);
	flags = ft_memalloc(ft_strlen(format));
	trav = format;
	while (*trav)
	{
		if (*trav == '%')
		{
			i = 0;
			trav++;
			while (!ft_str_contains(*trav))
				flags[i++] = *trav++;
			ft_manage_flags(flags, trav, arg);
		}
		else
			ft_putchar(*trav);
		trav++;
	}
	va_end(arg);
	free(flags);
	return (0);
}
