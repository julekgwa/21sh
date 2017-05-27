char	*ft_base(unsigned long num, int base)
{
	static char	representation[] = "0123456789ABCDEF";
	static char	buffer[50];
	char		*ptr;

	ptr = &buffer[49];
	*ptr = '\0';
	while (num != 0)
	{
		*--ptr = representation[num % base];
		num /= base;
	}
	return (ptr);
}
