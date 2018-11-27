#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len + src_len >= size)
		return (dest_len + src_len);
	ft_memcpy(dest + dest_len, src, src_len + 1);
	return (dest_len + src_len);
}
