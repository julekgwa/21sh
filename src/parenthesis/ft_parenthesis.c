/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:08:48 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/16 16:09:00 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_eof(int read_value, t_cmd *cmd)
{
	if (read_value == 0)
	{
		ft_putendl("21sh: unexpected EOF while looking for matching `\"'");
		ft_putendl("21sh: syntax error: unexpected end of file");
		cmd->get_line = "";
		return ;
	}
}

void	ft_remove_single_qoutes(t_cmd *cmd)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(cmd->get_line);
	while (i < len)
	{
		if (cmd->get_line[j] == 39 || cmd->get_line[j] == 34)
			j++;
		cmd->get_line[i] = cmd->get_line[j];
		i++;
		j++;
	}
}

void	ft_complete_cmd(t_cmd *cmd, struct termios *term)
{
	char	complete[BUFF_SIZE];
	char	line[SIZE];
	int		retvalue;

	ft_memset(complete, 0, BUFF_SIZE);
	ft_memset(line, 0, SIZE);
	if (ft_uneven(cmd->get_line))
	{
		ft_term_off(term);
		ft_putstr("\n> ");
		ft_strcpy(complete, cmd->get_line);
		while ((retvalue = read(0, line, SIZE)))
		{
			ft_strcat(complete, line);
			ft_memset(line, 0, SIZE);
			if (!ft_uneven(complete))
				break ;
			ft_putstr("> ");
		}
		ft_strcpy(cmd->get_line, complete);
		ft_check_eof(retvalue, cmd);
		ft_term_on(term);
	}
}
