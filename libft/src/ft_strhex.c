#include "libft.h"

void	ft_strhex(char *str)
{
	int	i;

	i = 0;
	ft_putstr("0x");
	while (str[i])
		ft_putchar(ft_tolower(str[i++]));
}
