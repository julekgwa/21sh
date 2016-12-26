/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:52:32 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/19 12:57:42 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_init_keyboard(struct termios *term, int *ac, char ***av)
{
	(void)ac;
	(void)av;
	if (tgetent(NULL, getenv("TERM")) < 1)
		return (0);
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ECHO | ECHOE | ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("ti", NULL), 1, ft_myputchar);
	tputs(tgetstr("vi", NULL), 1, ft_myputchar);
	ft_clear_screen();
	return (1);
}

int		ft_close_keyboard(struct termios *term)
{
	term->c_lflag |= (ECHO | ECHOE | ICANON);
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("te", NULL), 1, ft_myputchar);
	tputs(tgetstr("ve", NULL), 1, ft_myputchar);
	return (1);
}

void	ft_clear_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_myputchar);
}

void	ft_intermidiate(char **comm, int *pos, t_stack *hist, char *buf)
{
	if (buf[0] == 12)
		ft_ctrl_l(*comm, *pos, hist);
	else if (buf[0] == 18)
		hist->ctrl_r = 1;
	else if (ft_ctrl_b_f(buf))
		ft_move_word(*comm, pos, buf);
	else if (ft_up_down(buf))
		manage_up_down(&buf, comm, hist, pos);
	if (buf[0] == 16)
	{
		*comm = ft_get_prev_hist(*hist);
		*pos = ft_strlen(*comm);
	}
}

int		ft_is_inter(char *buf)
{
	if (buf[0] == 12 || buf[0] == 18 || buf[0] == 2 || buf[0] == 6)
		return (1);
	else if (buf[0] == 16)
		return (1);
	return (0);
}
