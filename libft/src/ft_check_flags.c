/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:14:02 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:14:11 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_check_flags(char *dest, char *traverse)
{
	char	*flags;
	char	*ttr;
	int		i;

	flags = dest;
	ttr = traverse;
	i = 0;
	while (!ft_str_contains(*ttr))
		flags[i++] = *ttr++;
	return (dest);
}
