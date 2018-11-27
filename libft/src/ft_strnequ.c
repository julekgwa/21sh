#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	equal;

	equal = ft_strncmp(s1, s2, n);
	if (equal == 0)
		return (1);
	return (0);
}
