/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 11:27:44 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/10 11:27:46 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_line_helper(char *text, int buf_size, char **line, const int fd)
{
	int		position;
	int		c;

	position = 0;
	while (1)
	{
		c = ft_getchar(fd);
		if (c == 0 || c == '\n')
		{
			text[position] = '\0';
			*line = text;
			return (1);
		}
		else
			text[position] = c;
		position++;
		if (position >= buf_size)
		{
			buf_size += BUFF_SIZE;
			text = ft_realloc(text, buf_size);
			if (!text)
				return (-1);
		}
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	char	*text;
	int		buf_size;

	buf_size = BUFF_SIZE;
	text = (char *)malloc(sizeof(char) * buf_size);
	if (fd < 0 || !text || !line)
		return (-1);
	return (ft_get_line_helper(text, buf_size, line, fd));
}
