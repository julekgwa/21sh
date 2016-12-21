#include "minishell.h"

char	*ft_get_dirname(char **needle)
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