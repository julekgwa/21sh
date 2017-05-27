#include "ft_printf.h"

int	ft_str_contains(char c)
{
	static char conversions[] = "sSpdDioOuUxXcC%";
	int			i;

	i = 0;
	while (conversions[i])
	{
		if (c == conversions[i++])
			return (1);
	}
	return (0);
}
