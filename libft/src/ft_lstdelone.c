#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **alist, void (*del)(void *, size_t))
{
	del((*alist)->content, (*alist)->content_size);
	free(*alist);
	*alist = NULL;
}
