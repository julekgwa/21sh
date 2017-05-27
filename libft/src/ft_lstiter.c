#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*tmp;

	tmp = lst;
	if (tmp)
	{
		while (tmp)
		{
			f(tmp);
			tmp = tmp->next;
		}
	}
}
