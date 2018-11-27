#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	while (*s1)
		s1++;
	while (*s2 && n--)
		*(s1++) = *s2++;
	*(++s1) = '\0';
	return (s1);
}
