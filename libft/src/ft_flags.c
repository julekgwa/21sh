int	ft_flags(char flag, char *search)
{
	while (*search)
	{
		if (*search == flag)
			return (1);
		search++;
	}
	return (0);
}
