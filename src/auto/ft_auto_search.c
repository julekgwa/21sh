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
		head = ft_search_binaries(head, split[len - 1]);
	else
		head = ft_search_system(head, split[len - 1]);
	freesplit(split);
	return (head);
}

void	ft_process_search(char *cmd, char *result, char *tmp, int *pos)
{
	char	*search;
	char	**split;
	int		len;

	split = SPLIT(cmd, ' ');
	search = split[ft_array_len(split) - 1];
	ft_get_dirname(&search);
	len = ft_strlen(search);
	if (tmp)
	{
		strcat(cmd, result + len);
		*pos = ft_strlen(cmd);
		strcat(cmd, tmp + 1);
	}
	else
	{
		strcat(cmd, result + len);
		*pos = ft_strlen(cmd);
	}
	freesplit(split);
}

void	ft_autocomplete(char **str, int *pos)
{
	t_list	*head;
	t_list	*tmp;
	char	search[256];
	char	*tmp_str;
	int		size;

	ft_memset(search, 0, 256);
	tmp_str = NULL;
	if (*pos < (int)ft_strlen(*str))
	{
		strncpy(search, *str, *pos);
		tmp_str = *str + *pos;
	}
	else
		strcpy(search, *str);
	head = ft_read_files(search);
	tmp = head;
	size = ft_list_size(head);
	if (size == 1)
	{
		ft_process_search(search, head->content, tmp_str, pos);
		strcpy(*str, search);
	}
	else
		ft_display_list(head);
	ft_freenodes(tmp);
}
