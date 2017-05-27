#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	while (*s2)
		s1[i++] = *s2++;
	s1[i] = '\0';
	return (s1);
}
