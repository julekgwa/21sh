#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*temp;

	temp = (void *)malloc(size + 1);
	if (temp)
		ft_bzero(temp, size + 1);
	return (temp);
}
