#include "minishell.h"

char	*ft_get_dirnames(char **needle)
{
	char	*dir_name;

	dir_name = ".";
	if (ft_strncmp(*needle, "~/", 2) == 0)
	{
		dir_name = getenv("HOME");
		*needle = *needle + 2;
	}
	else if (ft_strncmp(*needle, "/", 1) == 0)
	{
		dir_name = "/";
		*needle = *needle + 1;
	}
	else if (ft_strncmp(*needle, "../", 3) == 0)
	{
		dir_name = "..";
		*needle = *needle + 3;
	}
	else if (ft_strncmp(*needle, "./", 2) == 0)
		*needle = *needle + 2;
	return (dir_name);
}

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
		dir = ".";
	else if (ft_strncmp(dir, "~/", 2) == 0)
		dir = getenv("HOME");
	*needle = filename;
	return (dir);
}