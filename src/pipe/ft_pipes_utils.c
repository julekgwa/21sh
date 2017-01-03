/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 18:25:51 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 10:07:21 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_pipes(char *line, char **envp, t_stack *hist)
{
	int		pipes[2];
	char	**split_com;
	int		exec;

	split_com = ft_strsplit(line, '|');
	pipes[0] = ft_array_len(split_com);
	pipes[1] = CONTAINS(line, '|') ? 1 : 0;
	hist->counter = 0;
	exec = fork_pipes(pipes, split_com, envp, hist);
	freecopy(split_com);
	return (exec);
}
