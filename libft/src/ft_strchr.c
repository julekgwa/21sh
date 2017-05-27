#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[len] != '\0')
		len++;
	while ((i < len) && (s[i] != c))
		i++;
	if (s[i] == c)
		return (char *)&s[i];
	return (NULL);
}
