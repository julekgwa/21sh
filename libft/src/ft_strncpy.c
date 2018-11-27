#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	while (*src && len--)
		*dst++ = *src++;
	return (dst);
}
