int	ft_isdigit(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (!(ch >= 48 && ch <= 57))
		return (0);
	return (1);
}
