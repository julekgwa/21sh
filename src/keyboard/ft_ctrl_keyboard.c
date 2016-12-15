/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_keyboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:32:58 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:33:07 by goisetsi         ###   ########.fr       */
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

int		ft_enter_and_edit_keys(char *key_pressed, int *pos, char *comm)
{
	char	*key;
	int		i;

	key = key_pressed + 1;
	i = *pos - 1;
	if (key_pressed[0] == 127 || ft_strequ(key, "[3~"))
	{
		if (*pos > 0 && *comm)
		{
			ft_putstr("\33[2K\r");
			while (*(comm + i) != '\0')
			{
				*(comm + i) = *(comm + i + 1);
				i++;
			}
			*(comm + i) = '\0';
			*pos = *pos - 1;
			ft_cursor(comm, *pos + 1);
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

void	ft_cursor(char *comm, int pos)
{
	int		i;

	i = 0;
	ft_putstr("\33[2K\r");
	ft_putstr(GRN);
	ft_putstr("$> ");
	ft_putstr(RESET);
	if (comm == NULL)
		return ;
	while (comm[i])
	{
		if (i == pos - 1)
		{
			tputs(tgetstr("so", NULL), 1, ft_myputchar);
			ft_putchar(comm[i]);
			tputs(tgetstr("se", NULL), 1, ft_myputchar);
		}
		else
			ft_putchar(comm[i]);
		i++;
	}
	if ((int)ft_strlen(comm) < pos)
	{
		tputs(tgetstr("so", NULL), 1, ft_myputchar);
		ft_putchar(' ');
		tputs(tgetstr("se", NULL), 1, ft_myputchar);
	}
}
