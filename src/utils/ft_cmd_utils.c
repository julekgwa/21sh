/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:43 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/01 08:41:16 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ctrl_d(char **cmd, char *buf)
{
	if (buf[0] == 4 && ft_strequ(*cmd, ""))
	{
		ft_strcpy(*cmd, "exit");
		return (1);
	}
	return (0);
}

int	ft_spaces_tabs(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != 32 && s[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	ft_user_dir(char *dir, char **envp)
{
	char	*home;
	int		success;

	home = ft_strjoin(ft_get_env("$HOME", envp), dir + 1);
	success = chdir(home);
	if (success == 0)
	{
		free(home);
		return (1);
	}
	free(home);
	return (-1);
}

int	ft_term_off(struct termios *term)
{
	term->c_lflag |= (ECHO | ECHOE | ICANON);
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("ve", NULL), 1, ft_myputchar);
	return (1);
}

int	ft_term_on(struct termios *term)
{
	if (tgetent(NULL, getenv("TERM")) < 1)
		return (0);
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ECHO | ECHOE | ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("vi", NULL), 1, ft_myputchar);
	return (1);
}
