#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	while (*s)
		ft_putchar_fd(*(s++), fd);
	ft_putchar_fd('\n', fd);
}
