#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *ls;

	if (!lst)
		return (NULL);
	new = ft_lstnew(lst->content, lst->content_size);
	if (!new)
		return (NULL);
	ls = new;
	while (lst->next)
	{
		ls->next = f(lst->next);
		ls = ls->next;
		lst = lst->next;
	}
	return (new);
}
