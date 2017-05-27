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
