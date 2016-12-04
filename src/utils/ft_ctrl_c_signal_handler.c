/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c_signal_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:35:34 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:35:42 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c_signal_handler(int signum)
{
	exit(signum);
}

void	ft_print_error(char *erro)
{
	ft_putstr("21sh: ");
	ft_putstr(erro);
	ft_putstr(": command not found...\n");
}

void	prompt(t_cmd *command, t_stack *hist)
{
	char			*comm;
	char			*buf;
	int				pos;

	buf = ft_memalloc(GET_C_BUFF_SIZE);
	comm = ft_memalloc(1000);
	pos = 0;
	ft_putstr(GRN);
	ft_putstr("$> ");
	ft_putstr(RESET);
	tputs(tgetstr("so", NULL), 1, ft_myputchar);
	ft_putchar(' ');
	tputs(tgetstr("se", NULL), 1, ft_myputchar);
	command->get_line = ft_build_comm(hist, comm, buf, pos);
	free(buf);
}
