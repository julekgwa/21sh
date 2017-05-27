#include "libft.h"

void	ft_putnstr(char const *s, int len)
{
	while (*s && len--)
		ft_putchar(*(s++));
}
