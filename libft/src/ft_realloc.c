/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 08:28:08 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/10 10:41:37 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

    void	*ft_realloc(void *ptr, size_t len)
    {
    	void	*real;

    	real = (void *)malloc(len);
    	if (real)
        {
            memset(real, 0, len);
    		memcpy(real, ptr, strlen(ptr));
        }
    	free(ptr);
    	return (real);
    }
