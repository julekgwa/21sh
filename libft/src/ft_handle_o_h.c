/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_o_h.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:04:52 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:51:29 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_manage_o(int hash, int width, int l_justfy, char *o_x)
{
	int	str_len;

	str_len = ft_strlen(o_x);
	if (hash)
		width -= 1;
	if (l_justfy)
	{
		if (hash)
			ft_putstr("0");
		ft_strhex_lower(o_x);
		ft_manage_width(width - str_len);
	}
	else
	{
		ft_manage_width(width - str_len);
		if (hash)
			ft_putstr("0");
		ft_strhex_lower(o_x);
	}
}

void	ft_manage_type_x(int hash, int l_justfy, int width, char *o_x)
{
	int	str_len;

	str_len = ft_strlen(o_x);
	if (l_justfy)
	{
		if (hash)
			ft_putstr("0x");
		ft_strhex_lower(o_x);
		ft_manage_width(width - str_len);
	}
	else
	{
		ft_manage_width(width - str_len);
		if (hash)
			ft_putstr("0x");
		ft_strhex_lower(o_x);
	}
}

void	ft_manage_type_gx(int hash, int l_justfy, int width, char *o_x)
{
	int	str_len;

	str_len = ft_strlen(o_x);
	if (l_justfy)
	{
		if (hash)
			ft_putstr("0X");
		ft_putstr(o_x);
		ft_manage_width(width - str_len);
	}
	else
	{
		ft_manage_width(width - str_len);
		if (hash)
			ft_putstr("0X");
		ft_putstr(o_x);
		ft_manage_width(width - str_len);
	}
}

void	ft_handle_o_x(char *flags, char type, char *o_x)
{
	int	hash;
	int	width;
	int	l_justfy;

	hash = ft_flags('#', flags);
	l_justfy = ft_flags('-', flags);
	width = ft_find_width(flags);
	if (type == 'o' || type == 'O')
		ft_manage_o(hash, width, l_justfy, o_x);
	else if (type == 'x' || type == 'X')
	{
		if (hash)
			width -= 2;
		if (type == 'x')
			ft_manage_type_x(hash, l_justfy, width, o_x);
		else
			ft_manage_type_gx(hash, l_justfy, width, o_x);
	}
}
