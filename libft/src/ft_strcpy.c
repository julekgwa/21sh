#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*orig;

	orig = dst;
	while((*dst++ = *src++) != '\0')
		;
	return (orig);
}
