#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while ((*str1 == *str2) && *str1 && --n)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
