#include "libft.h"
#include "ft_printf.h"

void	ft_strhex_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(ft_tolower(str[i++]));
}
