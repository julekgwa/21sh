#include "libft.h"

void	ft_manage_width(int width)
{
	while (width > 0)
	{
		ft_putchar(' ');
		width--;
	}
}
