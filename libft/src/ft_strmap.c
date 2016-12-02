/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 16:32:29 by julekgwa          #+#    #+#             */
/*   Updated: 2016/05/11 16:33:00 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	i = -1;
	str = ft_memalloc(ft_strlen(s));
	if (str)
	{
		while (s[++i])
		{
			str[i] = f(s[i]);
		}
		str[i] = '\0';
	}
	return (str);
}
