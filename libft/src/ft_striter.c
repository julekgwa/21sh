void	ft_striter(char *s, void (*f)(char *))
{
	while (*s)
		f(&*(char *)(s++));
}
