/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 10:44:34 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/31 16:01:40 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_buff(char **com, int pos, char c, t_stack *hist)
{
	char	*copy;
	char	*buffer;
	int		i[2];

	copy = *com;
	buffer = ft_memalloc(ft_strlen(copy) + 1);
	buffer[ft_strlen(copy) + 1] = 0;
	if (pos >= (int)ft_strlen(copy))
	{
		ft_memcpy(buffer, copy, ft_strlen(copy));
		buffer[pos] = c;
	}
	else
	{
		i[0] = 0;
		i[1] = 0;
		while (copy[i[0]])
		{
			buffer[i[1]] = (i[1] == pos) ? c : copy[i[0]++];
			i[1]++;
		}
	}
	ft_memcpy(*com, buffer, ft_strlen(buffer));
	free(buffer);
	ft_cursor(*com, pos + 2, hist);
}

int		ft_ctrl_b_f(char *buf)
{
	if (buf[0] == 2 || buf[0] == 6 || EQUAL(buf, "5D") || EQUAL(buf, "5C"))
		return (1);
	else
		return (0);
}

void	ft_move_word(char *cmd, int *pos, char *buf)
{
	int	i;

	i = *pos;
	if (buf[0] == 2 || EQUAL(buf, "5D"))
	{
		if (cmd[i - 1] == ' ')
			i -= 2;
		while (i >= 0 && cmd[i] != ' ')
			i--;
		*pos = i + 1;
	}
	else if (buf[0] == 6 || EQUAL(buf, "5C"))
	{
		if (cmd[i + 1] == ' ')
			i += 2;
		while (cmd[i])
		{
			if (cmd[i] == ' ')
				break ;
			i++;
		}
		*pos = i + 1;
	}
}

void	ft_display_cmd(char *cmd, int pos)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (i == pos - 1)
		{
			tputs(tgetstr("so", NULL), 1, ft_myputchar);
			ft_putchar(cmd[i]);
			tputs(tgetstr("se", NULL), 1, ft_myputchar);
		}
		else
			ft_putchar(cmd[i]);
		i++;
	}
}
