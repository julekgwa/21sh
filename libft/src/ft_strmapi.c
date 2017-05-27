#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = -1;
	str = ft_memalloc(ft_strlen(s));
	if (str)
		while (s[++i])
			str[i] = f(i, s[i]);
	return (str);
}
