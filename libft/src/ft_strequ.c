#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int	equal;

	equal = ft_strcmp(s1, s2);
	if (equal == 0)
		return (1);
	return (0);
}
