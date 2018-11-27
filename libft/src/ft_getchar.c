#include "libft.h"

int	ft_getchar(const int fd)
{
	static char	buff[GET_C_BUFF_SIZE];
	static char	*chr;
	static int	pos = 0;
	static int	ret = 0;

	if (pos >= ret)
	{
		if ((ret = read(fd, buff, GET_C_BUFF_SIZE)) > 0)
		{
			chr = buff;
			pos = 0;
			return (*(chr + pos++));
		}
		else
		{
			return (0);
		}
	}
	else
	{
		return (*(chr + pos++));
	}
}
