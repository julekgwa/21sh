/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_contains.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:14:55 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:15:08 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_str_contains(char c)
{
	static char conversions[] = "sSpdDioOuUxXcC%";
	int			i;

	i = 0;
	while (conversions[i])
	{
		if (c == conversions[i++])
			return (1);
	}
	return (0);
}
