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
	t_list 	*head;
	char	**split;
	int		len;

	head = NULL;
	split = SPLIT(str, ' ');
	len = ft_array_len(split);
	if (ft_is_cmd(str) || ft_str_has(split[len - 1], ";|&"))
		head = ft_read_cmd_dir(head, split[len - 1]);
	freesplit(split);
	return (head);
}

void	ft_autocomplete(char *str)
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
