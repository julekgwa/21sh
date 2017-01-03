/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auto_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 02:04:05 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 09:21:43 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create(char *content, t_list *next)
{
	int		len;
	t_list	*new_node;

	len = ft_strlen(content);
	new_node = (t_list*)malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		ft_putstr("Error creating a new t_list.\n");
		exit(0);
	}
	new_node->content = (char *)malloc(sizeof(char) * (len + 1));
	if (new_node->content)
	{
		ft_strcpy(new_node->content, content);
		new_node->content_size = len;
		new_node->next = next;
	}
	return (new_node);
}

t_list	*prepend(t_list *head, char *content)
{
	t_list	*new_node;

	new_node = create(content, head);
	head = new_node;
	return (head);
}

t_list	*ft_read_files(char *str, char **envp)
{
	t_list	*head;
	char	**split;
	int		len;

	head = NULL;
	if (str[ft_strlen(str) - 1] == ' ')
		return (ft_scan_dir(head, " ", "."));
	split = SPLIT(str, ' ');
	len = ft_array_len(split);
	if (ft_start_with(split[len - 1], '$'))
		head = ft_auto_environ(head, envp, split[len - 1]);
	else if (ft_is_cmd(str) || ft_str_has(split[len - 1], ";|&"))
		head = ft_search_binaries(head, split[len - 1]);
	else
		head = ft_search_system(head, split[len - 1]);
	freecopy(split);
	return (head);
}

char	*ft_pro_search(char *cmd, char *result, char *tmp, int *pos)
{
	char	*search;
	char	**split;
	int		len;

	split = SPLIT(cmd, ' ');
	search = split[ft_array_len(split) - 1];
	if (ft_start_with(search, '$'))
		search = split[ft_array_len(split) - 1] + 1;
	free(ft_get_dirname(&search));
	len = ft_strlen(search);
	if (tmp)
	{
		ft_strcat(cmd, result + len);
		*pos = ft_strlen(cmd);
		ft_strcat(cmd, tmp + 1);
	}
	else
	{
		ft_strcat(cmd, result + len);
		if (!ft_is_dir(cmd))
			ft_strcat(cmd, " ");
		*pos = ft_strlen(cmd);
	}
	freecopy(split);
	return (cmd);
}

void	ft_autocomplete(char **str, int *pos, char **envp)
{
	t_list	*head;
	t_list	*tmp;
	char	search[256];
	char	*tmp_str;

	if (!ft_strequ(*str, ""))
	{
		ft_memset(search, 0, 256);
		tmp_str = NULL;
		if (*pos < (int)ft_strlen(*str))
		{
			ft_strncpy(search, *str, *pos);
			tmp_str = *str + *pos;
		}
		else
			ft_strcpy(search, *str);
		head = ft_read_files(search, envp);
		tmp = head;
		if (ft_lstsize(head) == 1)
			ft_strcpy(*str, ft_pro_search(search, head->content, tmp_str, pos));
		ft_display_list(head, ft_lstsize(head), ft_get_cols());
		ft_freenodes(tmp);
	}
}
