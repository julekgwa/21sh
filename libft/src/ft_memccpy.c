/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 09:16:15 by julekgwa          #+#    #+#             */
/*   Updated: 2016/05/10 09:16:38 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char		*n_src;
	unsigned char			*n_dest;
	size_t					i;

	i = 0;
	n_src = (unsigned char *)src;
	n_dest = (unsigned char *)dst;
	while (i < n)
	{
		if (*n_src == c)
			return (n_dest + 1);
		*n_dest++ = *n_src++;
		i++;
	}
	return (NULL);
}
