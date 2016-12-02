/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:13:08 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/05 17:16:01 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned	ft_num_digits(const int n)
{
	if (n >= 0 && n < 10)
		return (1);
	if (n < 0)
		return (ft_strlen(ft_itoa(n)));
	return (1 + ft_num_digits(n / 10));
}
