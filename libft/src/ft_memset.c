#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;

	dst = (unsigned char *)b;
	while (len-- > 0)
		*dst++ = (unsigned char)c;
	return (b);
}
