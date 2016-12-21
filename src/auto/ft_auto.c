/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 09:49:02 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/20 15:46:08 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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
			new->content = name;
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

t_list	*read_directory(char *prefix, size_t n)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;
	t_list			*head;
	// int				count;

	// count = 0;
	head = ft_new_item("head");
	if (!(p_dir = opendir("/home/julekgwa")))
	{
		printf("error: failed to open dir\n");
	}
	else
	{
		while ((p_dirent = readdir(p_dir)))
		{
			if (strncmp(prefix, p_dirent->d_name, n) == 0)
				ft_list(head, p_dirent->d_name);
		}
	}
	closedir(p_dir);
	return (head);
}

t_list	*ft_read_files(char *str)
{
	DIR				*dir;
	struct dirent	*dp;
	int				len;
	t_list 			*head;

	head = ft_new_item("head");
	len = strlen(str);
	if ((dir = opendir("/home/julekgwa")))
	{
		while ((dp = readdir(dir)) != NULL)
		{
			if (strncmp(str, dp->d_name, len) == 0)
				ft_list(head, dp->d_name);
		}
	}
	closedir(dir);
	return (head);
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
		if ((name = ft_read_files(prefix)))
			return (name);
	}
	return (NULL);
}

void	ft_print_results(char **prefix, int *pos)
{
	t_list	*head;
	t_list	*full;

	if ((full = ft_auto_comp(*prefix)))
	{
		head = full;
		if (*pos)
		{
			;
		}
		while (full)
		{
			printf("Match: %s\n", (char *)full->content);
			full = full->next;
		}
		ft_lstdel(&head, &ft_delcontent); //delete list
	}
}
