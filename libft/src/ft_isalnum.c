int	ft_isalnum(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90))
		return (1);
	else if ((ch >= 48 && ch <= 57))
		return (1);
	return (0);
}
