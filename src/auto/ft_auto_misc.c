/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auto_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 05:39:09 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 09:24:24 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_list(t_list *head, int size, int cols)
{
	int		max_len;
	int		curr_len;
	int		tmp_cols;
	t_list	*cursor;

	if (size > 1)
	{
		cursor = head;
		tmp_cols = cols;
		max_len = ft_get_max_strlen(head);
		ft_putchar('\n');
		while (cursor != NULL)
		{
			curr_len = ft_strlen(cursor->content);
			if (curr_len > tmp_cols)
			{
				write(1, "\r", 1);
				tmp_cols = cols;
			}
			ft_print_item(cursor->content, max_len - curr_len + 1);
			tmp_cols -= max_len + 1;
			cursor = cursor->next;
		}
		ft_putchar('\n');
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
	dir = (char *)malloc(sizeof(char) * BUFF_SIZE);
	ft_memset(dir, 0, sizeof(char) * BUFF_SIZE);
	ft_strncpy(dir, *needle, pos);
	if (ft_strequ(dir, ""))
		ft_strcpy(dir, ".");
	else if (ft_strncmp(dir, "~/", 2) == 0)
		ft_strcpy(dir, getenv("HOME"));
	*needle = filename;
	return (dir);
}

t_list	*ft_auto_environ(t_list *head, char **envp, char *needle)
{
	int		i;
	char	**tmp;
	int		len;

	i = 0;
	len = ft_strlen(needle);
	while (envp[i])
	{
		tmp = SPLIT(envp[i], '=');
		if (ft_strncmp(needle + 1, tmp[0], len - 1) == 0)
			head = prepend(head, tmp[0]);
		i++;
		freecopy(tmp);
	}
	return (head);
}

t_list	*ft_scan_dir(t_list *head, char *needle, char *dir_name)
{
	DIR				*dir;
	struct dirent	*dp;
	int				len;
	char			tmp[256];

	len = ft_strlen(needle);
	ft_memset(tmp, 0, 256);
	if ((dir = opendir(dir_name)))
	{
		while ((dp = readdir(dir)) != NULL)
		{
			ft_append_slash(tmp, dp->d_name);
			if (EQUAL(needle, " "))
			{
				if (!EQUAL(dp->d_name, ".") && !EQUAL(dp->d_name, ".."))
					head = prepend(head, tmp);
			}
			else if (ft_strncmp(needle, dp->d_name, len) == 0)
				head = prepend(head, tmp);
			ft_memset(tmp, 0, 256);
		}
	}
	closedir(dir);
	return (head);
}
