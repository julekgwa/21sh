#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (*big && len--)
	{
		if (*big == *little)
			if (ft_strncmp(big, little, little_len - 1) == 0)
				return ((char *)big);
		big++;
	}
	return (NULL);
}
