#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_memalloc(len + 1);
	if (sub)
		ft_memcpy(sub, s + start, len);
	return (sub);
}
