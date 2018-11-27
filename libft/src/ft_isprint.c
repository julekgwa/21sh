int	ft_isprint(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch >= 32 && ch < 127)
		return (1);
	return (0);
}
