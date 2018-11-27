#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new_str;

	new_str = (char *)ft_memalloc(size);
	if (new_str)
		ft_bzero(new_str, size);
	return (new_str);
}
