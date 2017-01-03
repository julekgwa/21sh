/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auto_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 09:49:02 by amarquez          #+#    #+#             */
/*   Updated: 2017/01/03 09:11:31 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_cmd(char *line)
{
	char		**split;
	static char	*sep[] = {";", "|", "&&", "||", 0};
	int			len;
	int			retval;

	retval = 0;
	split = SPLIT(line, ' ');
	len = ft_array_len(split);
	if (len == 1 && ft_isalpha(line[0]))
		retval = 1;
	else if (len > 2)
	{
		if (ft_in_array(sep, ft_array_len(sep), split[len - 2]))
			retval = 1;
	}
	freecopy(split);
	return (retval);
}

t_list	*ft_search_system(t_list *head, char *needle)
{
	char	*dir_name;

	dir_name = ft_get_dirname(&needle);
	head = ft_scan_dir(head, needle, dir_name);
	free(dir_name);
	return (head);
}

t_list	*ft_search_binaries(t_list *head, char *needle)
{
	int			i;
	static char	*search[] = {"/bin", "/usr/bin", "/usr/sbin", "/sbin", 0};

	i = -1;
	if (ft_start_with(needle, ';'))
		needle = needle + 1;
	head = ft_auto_builtins(head, needle);
	while (search[++i])
	{
		head = ft_scan_dir(head, needle, search[i]);
		if (ft_lstsize(head))
			break ;
	}
	return (head);
}

int		ft_str_has(char *str, char sep[])
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
