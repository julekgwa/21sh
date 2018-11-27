#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = -1;
	dup = ft_memalloc(ft_strlen(s1) + 1);
	if (!dup)
		return (dup);
	while (s1[++i])
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}
