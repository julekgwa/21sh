#include "libft.h"

void	ft_putendl(char const *s)
{
	while (*s)
		ft_putchar(*(s++));
	ft_putchar('\n');
}
