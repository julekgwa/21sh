/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logical_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:58:05 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 10:00:37 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_logical(char *line)
{
	char	**sp;
	int		i;

	i = 0;
	sp = SPLIT(line, ' ');
	while (sp[i])
	{
		if (EQUAL(sp[i], "&&") || EQUAL(sp[i], "||"))
		{
			freecopy(sp);
			return (1);
		}
		i++;
	}
	freecopy(sp);
	return (0);
}

char	*ft_get_logical_sep(char *line)
{
	char	**sp;
	int		i;
	char	*sep;

	i = 0;
	sep = NULL;
	sp = SPLIT(line, ' ');
	while (sp[i])
	{
		if (EQUAL(sp[i], "&&") || EQUAL(sp[i], "||"))
		{
			sep = strdup(sp[i]);
			freecopy(sp);
			return (sep);
		}
		i++;
	}
	freecopy(sp);
	return (sep);
}

void	split_by_word(char av[][BUFF_SIZE], char **arr, char *word)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		if (strcmp(arr[i], word))
		{
			strcat(av[j], arr[i]);
			strcat(av[j], " ");
		}
		else
			++j;
		++i;
	}
}

void	ft_log_op(t_cmd *cmd, t_env *envp, struct termios *t, t_stack *hist)
{
	char	log[BUFF_SIZE][BUFF_SIZE];
	char	*sep;
	int		i;
	t_cmd	logic;
	int		exec;

	memset(log, 0, sizeof(log[0][0]) * BUFF_SIZE * BUFF_SIZE);
	exec = 0;
	sep = ft_get_logical_sep(cmd->get_line);
	i = 0;
	split_by_word(log, cmd->user_comm, sep);
	while (log[i] && log[i][0])
	{
		logic.get_line = log[i];
		if (exec == -1 && EQUAL(sep, "&&"))
			break ;
		exec = ft_pro_cmd(&logic, envp, t, hist);
		if (exec == 0 && EQUAL(sep, "||"))
			break ;
		i++;
	}
	free(sep);
}
