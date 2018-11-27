#include "libft.h"

void	ft_putwchar_t(wchar_t *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}
