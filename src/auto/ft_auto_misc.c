#include "minishell.h"

void	ft_display_list(t_list *head)
{
    t_list *cursor;

    cursor = head;
    ft_putchar('\n');
    while(cursor != NULL)
    {
        ft_putendl(cursor->content);
        cursor = cursor->next;
    }
}

char	*ft_get_search_value(char *needle, int *pos)
{
	int	len;

	len = ft_strlen(needle);
	if (!CONTAINS(needle, '/'))
	{
		*pos = 0;
		return (needle);
	}
	while (len >= 0)
	{
		if (needle[len] == '/')
		{
			len++;
			break ;
		}
		len--;
	}
	*pos = len;
	return (needle + len);
}

char	*ft_get_dirname(char **needle)
{
	char	*dir;
	char	*filename;
	int		pos;

	pos = 0;
	filename = ft_get_search_value(*needle, &pos);
	dir = (char *)malloc(sizeof(char) * (strlen(*needle) + 1));
	ft_memset(dir, 0, sizeof(char) * (strlen(*needle) + 1));
	ft_strncpy(dir, *needle, pos);
	if (ft_strequ(dir, ""))
		strcpy(dir, ".");
	else if (ft_strncmp(dir, "~/", 2) == 0)
		dir = getenv("HOME");
	*needle = filename;
	return (dir);
}