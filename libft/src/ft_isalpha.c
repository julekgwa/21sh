int	ft_isalpha(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (!((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90)))
		return (0);
	return (1);
}
