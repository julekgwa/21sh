#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	max;
	int				sign;

	sign = -1;
	max = n;
	if (n < 0)
	{
		ft_putchar('-');
		max = sign * n;
	}
	if (max >= 10)
	{
		ft_putnbr(max / 10);
		ft_putnbr(max % 10);
	}
	else
		ft_putchar(max + '0');
}
