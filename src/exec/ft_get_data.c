/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:09:59 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/08 22:10:32 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hash_table_bin(t_hash *table[], char **path)
{
	DIR				*dir;
	struct dirent	*dp;
	char			bin[256];
	int				i;

	i = -1;
	ft_memset(bin, 0, 256);
	while (path[++i])
	{
		if ((dir = opendir(path[i])))
		{
			while ((dp = readdir(dir)) != NULL)
			{
				ft_strcpy(bin, path[i]);
				ft_strcat(bin, "/");
				ft_strcat(bin, dp->d_name);
				if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, ".."))
					ft_insert_item(table, dp->d_name, bin);
			}
			ft_memset(bin, 0, 256);
		}
		closedir(dir);
	}
}

char	*ft_build_exec(char **split, t_stack *hist)
{
	unsigned int	code;
	char			*str;
	t_hash			*tmp;

	code = ft_hash_code(QUOTES(split[0]));
	tmp = ft_search(hist->hash[code], split[0]);
	if (code > MAX_HASH || !tmp)
		return (NULL);
	str = tmp->value;
	if (access(str, F_OK) == 0)
		return (str);
	return (NULL);
}

int		ft_is_execute(char *command)
{
	if (access(command, F_OK) == 0)
		return (1);
	return (0);
}

int		ft_execute(char *command, t_cmd *cmd, char **envp, t_stack *hist)
{
	pid_t	pid;
	int		status;
	int		value;

	value = 0;
	if ((pid = fork()) < 0)
		exit(1);
	else if (pid == 0)
	{
		if (ft_is_pipe_or_redirect(cmd->get_line))
			ft_process_pipes(cmd->get_line, envp, hist);
		else
			ft_execute_cmd(command, cmd->user_comm, envp);
		exit(0);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				value = -1;
		}
	}
	return (value);
}

int		ft_array_len(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (0);
	while (*arr)
	{
		count++;
		arr++;
	}
	return (count);
}
