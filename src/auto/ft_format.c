/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 20:30:12 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 09:16:05 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_cols(void)
{
	struct winsize	ws;
	int				fd;
	int				cols;

	cols = 0;
	fd = open("/dev/tty", O_RDWR);
	if (fd < 0)
		return (0);
	if (ioctl(fd, TIOCGWINSZ, &ws) < 0)
		return (0);
	close(fd);
	cols = ws.ws_col;
	return (cols);
}

void	ft_print_item(char *str, int num_sp)
{
	char sp;

	sp = ' ';
	write(1, str, ft_strlen(str));
	while (num_sp--)
		write(1, &sp, 1);
}

int		ft_get_max_strlen(t_list *head)
{
	int		len;
	t_list	*cursor;

	len = 0;
	cursor = head;
	while (cursor != NULL)
	{
		if ((int)ft_strlen(cursor->content) > len)
			len = ft_strlen(cursor->content);
		cursor = cursor->next;
	}
	return (len);
}

void	ft_append_slash(char tmp[], char *filename)
{
	ft_strcpy(tmp, filename);
	if (ft_is_dir(tmp))
		ft_strcat(tmp, "/");
}

t_list	*ft_auto_builtins(t_list *head, char *needle)
{
	int			i;
	int			len;
	static char	*cmd[] = {
		"history", "setenv", "unsetenv",
		"exit", "clear", "export", "unset",
		0
	};

	i = 0;
	len = ft_strlen(needle);
	while (cmd[i])
	{
		if (ft_strncmp(needle, cmd[i], len) == 0)
			head = prepend(head, cmd[i]);
		i++;
	}
	return (head);
}
