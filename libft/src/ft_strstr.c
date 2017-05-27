#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
			if (ft_strncmp(big, little, little_len - 1) == 0)
				return ((char *)big);
		big++;
	}
	return (NULL);
}
