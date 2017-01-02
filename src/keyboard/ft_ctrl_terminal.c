/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:52:32 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/02 07:56:58 by julekgwa         ###   ########.fr       */
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
	int	tmp_pos;

	tmp_pos = *pos;
	if (buf[0] == 12)
		ft_ctrl_l(*comm, *pos, hist);
	else if (buf[0] == 18)
		hist->ctrl_r = 1;
	else if (ft_ctrl_b_f(buf))
		ft_move_word(*comm, pos, buf);
	else if (ft_up_down(buf))
		manage_up_down(&buf, comm, hist, pos);
	else if (buf[0] == 20 || buf[0] == 8)
		ft_swap_or_del_chars(*comm, buf, pos);
	else if (EQUAL(buf, "5A") || EQUAL(buf, "5B"))
	{
		ft_memset(*comm, 0, BUFF_SIZE);
		ft_strcpy(*comm, ft_keys_up_down(buf, hist, pos));
		if ((int)ft_strlen(*comm) > tmp_pos)
			*pos = tmp_pos;
	}
}

int		ft_is_inter(char *buf)
{
	if (buf[0] == 12 || buf[0] == 18 || buf[0] == 2 || buf[0] == 6)
		return (1);
	else if (EQUAL(buf, "5D") || EQUAL(buf, "5C") || buf[0] == 20)
		return (1);
	else if (EQUAL(buf, "5A") || EQUAL(buf, "5B"))
		return (1);
	else if (buf[0] == 8)
		return (1);
	return (0);
}
