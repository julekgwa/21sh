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

int	ft_is_cmd(char *line)
{
	char		**split;
	static char	*sep[] = {";", "|", "&&", "||", 0};
	int			len;
	int			retval;

	retval = 0;
	split = SPLIT(line, ' ');
	len = ft_array_len(split);
	if (len == 1)
		retval = 1;
	else if (len > 2)
	{
		if (ft_in_array(sep, ft_array_len(sep), split[len -2]))
			retval = 1;
	}
	freesplit(split);
	return (retval);
}

int	ft_in_array(char **av, int len, char *needle)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_strequ(av[i], needle))
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_search_system(t_list *head, char *needle)
{
	DIR				*dir;
	struct dirent	*dp;
	int				len;
	char			*dir_name;

	dir_name = ft_get_dirname(&needle);
	len = ft_strlen(needle);
	if ((dir = opendir(dir_name)))
	{
		while ((dp = readdir(dir)) != NULL)
		{
			if (ft_strncmp(needle, dp->d_name, len) == 0)
				head = prepend(head, dp->d_name);
		}
	}
	closedir(dir);
	return (head);
}

t_list	*ft_search_binaries(t_list *head, char *needle)
{
	DIR				*dir;
	struct dirent	*dp;
	int				len;
	int				i;
	char			*search[] = {"/bin", "/usr/bin", "/usr/sbin", "/sbin", 0};

	i = 0;
	if (ft_start_with(needle, ';'))
		needle = needle + 1;
	len = ft_strlen(needle);
	while (search[i])
	{
		if ((dir = opendir(search[i])))
		{
			while ((dp = readdir(dir)) != NULL)
			{
				if (strncmp(needle, dp->d_name, len) == 0)
					head = prepend(head, dp->d_name);
			}
		}
		closedir(dir);
		if (ft_list_size(head))
			break ;
		i++;
	}
	return (head);
}

int	ft_str_has(char *str, char sep[])
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (CONTAINS(str, sep[i]))
			return (1);
		i++;
	}
	return (0);
}