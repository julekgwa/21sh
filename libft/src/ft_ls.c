#include "ft_ls.h"

int		ft_is_valid_arg(const char *str)
{
	str++;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != 'l' && *str != 'a' && *str != 'R' && *str != 'r' && *str != 't')
			return (0);
		str++;
	}
	return (1);
}

int		ft_get_dir(char **av)
{
	int	i;

	i = 0;
	av++;
	while (*av)
	{
		if (!ft_is_valid_arg(*av) || ft_strcmp(*av, "/") == 0)
			i++;
		av++;
	}
	return (i);
}

char	*ft_ls_args(char **args)
{
	static char	buffer[6];
	char		*ptr;
	int			i;
	char		*tmp;

	ptr = &buffer[5];
	*ptr = '\0';
	while (*args)
	{
		i = 1;
		if (ft_is_valid_arg(*args))
		{
			tmp = *args;
			while (tmp[i])
			{
				*--ptr = tmp[i];
				i++;
			}
		}
		args++;
	}
	return (ptr);
}

int ft_ls(char **av)
{
	char	*args;
	int		num_dir;
	t_file	*dir;

	args = ft_ls_args(av);
	dir = ft_new_file("head", "head");
	num_dir = ft_get_dir(av);
	if (num_dir)
	{
		av++;
		while (*av)
		{
			if (!ft_is_valid_arg(*av) || ft_strcmp(*av, "/") == 0)
				ft_read_dir(*av, &dir, args);
			av++;
		}
	}
	else
	{
		ft_read_dir(".", &dir, args);
	}
	return (0);
}