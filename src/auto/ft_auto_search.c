#include "minishell.h"

t_list	*create(char *content,t_list* next)
{
	int	len;

	len = strlen(content);
	t_list	*new_node = (t_list*)malloc(sizeof(t_list));
	if(new_node == NULL)
	{
		ft_putstr("Error creating a new t_list.\n");
		exit(0);
	}
	new_node->content = (char *)malloc(sizeof(char) * (len + 1));
	if (new_node->content)
	{
		strcpy(new_node->content, content);
		new_node->content_size = len;
		new_node->next = next;
	}
	return (new_node);
}

t_list	*prepend(t_list* head,char *content)
{
	t_list	*new_node;

	new_node = create(content, head);
	head = new_node;
	return (head);
}

t_list	*ft_new_item(char *name)
{
	t_list	*new;
	int		len;

	len = strlen(name);
	new = (t_list *)malloc(sizeof(t_list));
	if (new)
	{
		new->content = (char *)malloc(sizeof(char) * (len + 1));
		if (new->content)
		{
			strcpy(new->content, name);
			new->content_size = len;
			new->next = NULL;
		}
	}
	return (new);
}

void	ft_list(t_list *head, char *name)
{
	t_list	*tmp;
	t_list	*next;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	next = ft_new_item(name);
	tmp->next = next;
}

void	ft_freenodes(t_list *head)
{
	t_list	*tmp;
	while ((tmp = head) != NULL)
	{
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

int	ft_list_size(t_list *begin_list)
{
	int		i;
	t_list	*list;

	i = 0;
	list = begin_list;
	if (list)
	{
		while (list)
		{
			i++;
			list = list->next;
		}
	}
	return (i);
}

t_list	*ft_read_files(char *str)
{
	DIR				*dir;
	struct dirent	*dp;
	int				len;
	t_list 			*head;

	head = NULL;
	len = strlen(str);
	if ((dir = opendir("/home/julekgwa")))
	{
		while ((dp = readdir(dir)) != NULL)
		{
			if (strncmp(str, dp->d_name, len) == 0)
				head = prepend(head, dp->d_name);
		}
	}
	closedir(dir);
	return (head);
}

void	ft_testing(char *str)
{
	t_list	*head;
	t_list	*tmp;
	int		size;

	head = ft_read_files(str);
	tmp = head;
	size = ft_list_size(head);
	if (size == 1)
	{
		ft_putendl(head->content);
	}
	else
	{
		while (head)
		{
			ft_putendl(head->content);
			head = head->next;
		}
	}
	ft_freenodes(tmp);
}
