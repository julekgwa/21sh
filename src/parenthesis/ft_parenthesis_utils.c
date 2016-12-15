#include "minishell.h"

int		ft_uneven(char *str)
{
	int	countsingle;
	int	countdouble;

	countsingle = 0;
	countdouble = 0;
	while (*str)
	{
		if (*str == '\"')
			countdouble++;
		if (*str == '\'')
			countsingle++;
		str++;
	}
	if ((countdouble % 2 == 0) && (countsingle % 2 == 0))
		return (0);
	else
		return (1);
}