/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhex_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:03:57 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/10 10:46:27 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_strhex_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(ft_tolower(str[i++]));
}
