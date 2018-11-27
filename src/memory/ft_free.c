#include "minishell.h"

void	freecopy(char **copy)
{
	int	i;

	i = 0;
	if (copy != NULL)
	{
		while (copy[i] != NULL)
		{
			free(copy[i]);
			i++;
		}
		free(copy);
	}
}

void	freesplit(char **split)
{
	free(split[0]);
	free(split);
}

void	ft_free_str(char *str, char *join)
{
	free(str);
	free(join);
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
