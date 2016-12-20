#include "minishell.h"

t_list	*read_directory(char *prefix, size_t n)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;
	t_list			*head;
	// int				count;

	// count = 0;
	head = ft_lstnew(NULL, 0);
	head->next = NULL;
	if ((p_dir = opendir("/home/julekgwa")))
	{
		while ((p_dirent = readdir(p_dir)))
		{
			if (ft_strnequ(p_dirent->d_name, prefix, n))
				ft_lstadd(&head, ft_lstnew(p_dirent->d_name, ft_strlen(p_dirent->d_name) + 1));
		}
	}
	closedir(p_dir);
	return (head);
}

size_t        ft_lstlen(t_list *temp)
{
    int    length;

    length = 0;
    while (temp)
    {
        length++;
        temp = temp->next;
    }
    return (length);
}

void	ft_delcontent(void *a, size_t len)
{
	(void)len;
	ft_memdel(&a);
}

t_list	*ft_auto_comp(char *prefix)
{
	size_t	n;
	t_list	*name;

	n = ft_strlen(prefix);
	name = NULL;
	if (n > 0) 
	{
		if ((name = read_directory(prefix, n)))
			return (name);
	}
	return (NULL);
}

void	ft_print_results(char *prefix)
{
	t_list	*head;
	t_list	*full;
	size_t	size;

	size = 0;
	full = ft_auto_comp(prefix);
	if (full)
	{
		if ((size = ft_lstlen(full)) > 0)
		{
			head = full;
			ft_putchar('\n');
			while (full->content)
			{
				ft_putendl((char *)full->content);
				full = full->next;
			}
		} 
		ft_lstdel(&head, &ft_delcontent); //delete list
	}
}