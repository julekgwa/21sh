/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 16:47:46 by julekgwa          #+#    #+#             */
/*   Updated: 2016/05/15 16:48:29 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	char	*str;

	if (n > 2147483647)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char *))))
		return (NULL);
	if (n >= 0)
	{
		while (n != 0)
		{
			*(--str) = '0' + (n % 10);
			n /= 10;
		}
		return (str);
	}
	else
	{
		while (n != 0)
		{
			*(--str) = '0' - (n % 10);
			n /= 10;
		}
		*(--str) = '-';
	}
	return (str);
}
