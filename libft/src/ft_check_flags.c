#include "libft.h"
#include "ft_printf.h"

char	*ft_check_flags(char *dest, char *traverse)
{
	char	*flags;
	char	*ttr;
	int		i;

	flags = dest;
	ttr = traverse;
	i = 0;
	while (!ft_str_contains(*ttr))
		flags[i++] = *ttr++;
	return (dest);
}
