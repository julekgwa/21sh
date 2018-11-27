#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (lst)
	{
		if (!content)
		{
			lst->content = NULL;
			lst->content_size = 0;
		}
		else
		{
			lst->content = ft_memalloc(content_size);
			if (!lst->content)
				return (NULL);
			ft_memcpy(lst->content, content, content_size);
			lst->content_size = content_size;
		}
		lst->next = NULL;
	}
	return (lst);
}
