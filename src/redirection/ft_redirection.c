/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:33:15 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/29 21:52:26 by julekgwa         ###   ########.fr       */
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

int		ft_file_redirection(char **red, char **envp, int arrow[])
{
	char	*file_name;
	int		arrow_pos;

	arrow[0] = 0;
	arrow_pos = ft_arrow_pos(red);
	file_name = red[arrow_pos + 1];
	if (ft_get_less_than(red) > 0)
		arrow[0] = 2;
	else if (STD_INOUT(red) != 2 && ft_in_array(red, LENGTH(red), ">>"))
		arrow[0] = ft_find_arrow(red);
	if (ft_is_less_than(red))
		arrow_pos = ft_process_here_doc(red, arrow[1]);
	else if (ft_is_file_descriptor_aggr(red))
		arrow_pos = ft_manage_file_descriptors(red);
	else
		ft_open_file(file_name, arrow[0]);
	ft_redirect_left_right(red);
	red[arrow_pos] = 0;
	return (ft_execute_cmd(red[0], &red[0], envp));
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

int		ft_find_arrow(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strequ(str[i], ">>"))
			j = 1;
		i++;
	}
	return (j);
}
