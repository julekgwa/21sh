#include "libft.h"
#include "ft_printf.h"

int	ft_find_width(char *flags)
{
	int	width;
	int	found;

	width = 0;
	found = 0;
	while (*flags != '.' && found == 0)
	{
		if (*flags >= 48 && *flags <= 57)
		{
			width = ft_atoi(flags);
			found = 1;
		}
		flags++;
	}
	return (width);
}
