/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:16:59 by julekgwa          #+#    #+#             */
/*   Updated: 2016/05/14 16:47:10 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	const char	*str;

	ch = (char)c;
	str = NULL;
	if (ch == '\0')
		return ((char *)str);
	while (*s)
	{
		if (*s == '\0')
			return (0);
		else if (*s == ch)
			str = s;
		s++;
	}
	s = str;
	return (char *)s;
}
