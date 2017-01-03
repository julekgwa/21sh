/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 13:04:38 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/19 13:04:40 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_read_here_doc(int fd, char *s)
{
	char	line[SIZE];
	char	*list[SIZE];
	int		i;
	ssize_t	retval;

	ft_memset(line, 0, SIZE);
	ft_memset(list, 0, SIZE * sizeof(*list));
	i = 0;
	retval = 0;
	while ((retval = read(1, line, SIZE)) > 0)
	{
		if (!ft_strncmp(line, s, ft_strlen(line) - 1))
			break ;
		else
			list[i++] = ft_strdup(line);
		ft_memset(line, 0, SIZE);
	}
	i = -1;
	while (list[++i])
		write(fd, list[i], ft_strlen(list[i]));
	return (retval);
}

int		ft_is_redirect_in_out(char **cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (ft_strequ(cmd[i], "<") || ft_strequ(cmd[i], "<<"))
			count++;
		else if (ft_strequ(cmd[i], ">") || ft_strequ(cmd[i], ">>"))
			count++;
		i++;
	}
	return (count);
}

void	ft_redirect_left_right(char **cmd)
{
	int		arrow;
	int		pos;
	char	*filename;

	arrow = 0;
	pos = 0;
	if (STD_INOUT(cmd) != 2)
		return ;
	arrow = ft_find_arrow(cmd);
	if (arrow == 0)
		pos = ft_get_here_doc_pos(cmd, ">");
	else if (arrow == 1)
		pos = ft_get_here_doc_pos(cmd, ">>");
	if (cmd[pos + 1] == NULL)
	{
		ft_putendl("21sh: syntax error near unexpected token `newline'");
		return ;
	}
	filename = cmd[pos + 1];
	ft_open_file(filename, arrow);
}

int		ft_is_pipe_or_redirect(char *line)
{
	if (CONTAINS(line, '|') || CONTAINS(line, '>') || CONTAINS(line, '<'))
		return (1);
	return (0);
}
