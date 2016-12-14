/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:33:15 by julekgwa          #+#    #+#             */
/*   Updated: 2016/09/10 16:36:18 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_file(char *file_name, int arrow)
{
	int	fd;

	if (arrow == 1)
	{
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		dup2(fd, 1);
	}
	else if (arrow == 2)
	{
		fd = open(file_name, O_RDONLY);
		dup2(fd, 0);
	}
	else
	{
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		dup2(fd, 1);
	}
	close(fd);
}

int		ft_file_redirection(char **red, char **envp)
{
	char	*file_name;
	int		arrow;
	int		count;
	int		arrow_pos;

	arrow = 0;
	count = 0;
	file_name = red[ft_array_len(red) - 1];
	arrow_pos = ft_arrow_pos(red);
	if (ft_get_less_than(red) > 0)
		arrow = 2;
	while (red[count])
	{
		if (ft_strequ(red[count], ">>"))
		{
			arrow = 1;
			break ;
		}
		count++;
	}
	if (ft_is_file_descriptor_aggr(red))
		arrow_pos = ft_manage_file_descriptors(red);
	else
		ft_open_file(file_name, arrow);
	red[arrow_pos] = 0;
	return (execve(red[0], &red[0], envp));
}

int		ft_arrow_pos(char **cmd)
{
	int	indx;

	indx = 0;
	while (*cmd)
	{
		if (ft_contains(*cmd, '>') || ft_contains(*cmd, '<'))
			return (indx);
		indx++;
		cmd++;
	}
	return (indx);
}

int		ft_is_redirect(char **cmd)
{
	while (*cmd)
	{
		if (ft_contains(*cmd, '>') || ft_contains(*cmd, '<'))
			return (1);
		cmd++;
	}
	return (0);
}

char	**ft_remove_arrow(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ft_is_redirect(str))
		return (str);
	while (str[j])
	{
		if (ft_strequ(str[j], "<"))
			j++;
		str[i] = str[j];
		i++;
		j++;
	}
	str[--j] = 0;
	return (str);
}
