/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 03:52:52 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/29 03:52:55 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_lstsize(t_list *begin_list)
{
    int     i;
    t_list  *list;

    i = 0;
    list = begin_list;
    if (list)
    {
        while (list)
        {
            i++;
            list = list->next;
        }
    }
    return (i);
}
