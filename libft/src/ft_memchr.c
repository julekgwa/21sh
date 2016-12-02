/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:00:21 by julekgwa          #+#    #+#             */
/*   Updated: 2016/05/16 11:34:25 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *r;

	r = (unsigned char *)s;
	while (n > 0)
	{
		if (*r++ == (unsigned char)c)
			return ((void *)r - 1);
		n--;
	}
	return (NULL);
}
