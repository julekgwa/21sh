/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_keyboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:53:08 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/08 16:36:05 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_function_keys(char *key_pressed)
{
	char	*key;

	key = key_pressed + 1;
	if (ft_strequ(key, "OP"))
		ft_putendl("F1");
	else if (ft_strequ(key, "OQ"))
		ft_putendl("F2");
	else if (ft_strequ(key, "OR"))
		ft_putendl("F3");
	else if (ft_strequ(key, "OS"))
		ft_putendl("F4");
	else if (ft_strequ(key, "[15~"))
		ft_putendl("F5");
	else
		return (0);
	return (1);
}

int		ft_character_keys(char *key_pressed)
{
	if (key_pressed[0] >= 32 && key_pressed[0] <= 126 && *key_pressed != 27)
		return (1);
	else
		return (0);
}

int		ft_enter_and_edit_keys(char *press, int *pos, char *cmd, t_stack *hist)
{
	char	*key;
	int		i;

	key = press + 1;
	i = *pos - 1;
	if (press[0] == 127 || ft_strequ(key, "[3~"))
	{
		if (*pos > 0 && *cmd)
		{
			ft_putstr("\33[2K\r");
			while (*(cmd + i) != '\0')
			{
				*(cmd + i) = *(cmd + i + 1);
				i++;
			}
			*(cmd + i) = '\0';
			*pos = *pos - 1;
			ft_cursor(cmd, *pos + 1, hist);
		}
		return (1);
	}
	else
		return (0);
	return (1);
}

int		ft_navigation_keys(char *key_pressed, int *pos, char *comm)
{
	char	*key;

	key = key_pressed + 1;
	if (ft_strequ(key, "[D"))
	{
		if (*pos > 0)
			*pos = *pos - 1;
	}
	else if (ft_strequ(key, "[C"))
	{
		if ((int)ft_strlen(comm) > *pos)
			*pos = *pos + 1;
	}
	else if (ft_strequ(key, "[H"))
		*pos = 0;
	else if (ft_strequ(key, "[F"))
		*pos = (int)ft_strlen(comm);
	else
		return (0);
	return (1);
}

void	ft_cursor(char *comm, int pos, t_stack *hist)
{
	hist->counter = 0;
	if (hist->ctrl_r)
		ft_bck_i_search(comm, pos, hist);
	else
	{
		ft_cmd_prompt();
		while (!(comm == NULL) && comm[hist->counter])
		{
			if (hist->counter == pos - 1)
			{
				tputs(tgetstr("so", NULL), 1, ft_myputchar);
				ft_putchar(comm[hist->counter]);
				tputs(tgetstr("se", NULL), 1, ft_myputchar);
			}
			else
				ft_putchar(comm[hist->counter]);
			hist->counter++;
		}
		if ((int)ft_strlen(comm) < pos)
		{
			tputs(tgetstr("so", NULL), 1, ft_myputchar);
			ft_putchar(' ');
			tputs(tgetstr("se", NULL), 1, ft_myputchar);
		}
	}
}
