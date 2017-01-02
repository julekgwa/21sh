/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:31:47 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/01 23:30:21 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_paste(char **cmd, int *pos, t_stack *hist)
{
	ft_strcat(*cmd, hist->paste);
	*pos = ft_strlen(*cmd);
}

void	ft_cut(char **cmd, char *buf, int *pos, t_stack *hist)
{
	int		len;

	len = ft_strlen(*cmd);
	if (buf[0] == 11)
	{
		if (*pos == len || *pos > len)
			hist->paste = "";
		else
		{
			hist->paste = strndup(*cmd, *pos);
			*cmd = *cmd + *pos;
			*pos = ft_strlen(*cmd);
		}
	}
	else if (buf[0] == 24)
	{
		if (ft_strequ(*cmd, ""))
			return ;
		hist->paste = ft_strdup(*cmd);
		ft_bzero(*cmd, len);
		*pos = 0;
	}
}

void	ft_copy(char **cmd, char *buf, int *pos, t_stack *hist)
{
	int		len;

	len = ft_strlen(*cmd);
	if (buf[0] == 23)
	{
		if (*pos == len || *pos > len)
			hist->paste = "";
		else
		{
			hist->paste = strndup(*cmd, *pos);
		}
	}
	else if (buf[0] == 7)
	{
		if (ft_strequ(*cmd, ""))
			return ;
		hist->paste = ft_strdup(*cmd);
	}
}

void	ft_copy_n_paste(char **cmd, char *buf, int *pos, t_stack *hist)
{
	if (buf[0] == 22)
		ft_paste(cmd, pos, hist);
	else if (buf[0] == 11 || buf[0] == 24)
		ft_cut(cmd, buf, pos, hist);
	else if (buf[0] == 23 || buf[0] == 7)
		ft_copy(cmd, buf, pos, hist);
}

int		ft_is_copy_n_paste(char *buf)
{
	if (buf[0] == 11 || buf[0] == 24 || buf[0] == 22)
		return (1);
	else if (buf[0] == 23 || buf[0] == 7)
		return (1);
	return (0);
}
