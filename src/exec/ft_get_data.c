/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:09:59 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/27 17:10:01 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**getpath(char **envp)
{
	int		i;
	char	**s1;
	char	**s2;

	i = 0;
	while (envp[i])
	{
		s1 = ft_strsplit(envp[i], '=');
		if (ft_strequ(s1[0], "PATH"))
		{
			s2 = ft_strsplit(s1[1], ':');
			freecopy(s1);
			return (s2);
		}
		i++;
		freecopy(s1);
	}
	return (NULL);
}

void	ft_hash_table_bin(t_hash *table[], char **path)
{
	DIR				*dir;
	struct dirent	*dp;
	char			bin[256];
	int				i;

	i  = -1;
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

	code = ft_hash_code(split[0]);
	str = ft_search(hist->hash[code], split[0])->value;
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

void	ft_execute(char *command, t_cmd *cmd, char **envp, t_stack *hist)
{
	pid_t	pid;
	int		status;
	int		pipes[2];
	char	**split_com;

	if ((pid = fork()) < 0)
		exit(1);
	else if (pid == 0)
	{
		if (ft_is_pipe_or_redirect(cmd->get_line))
		{
			split_com = ft_strsplit(cmd->get_line, '|');
			pipes[0] = ft_array_len(split_com);
			pipes[1] = CONTAINS(cmd->get_line, '|') ? 1 : 0;
			hist->counter = 0;
			fork_pipes(pipes, split_com, envp, hist);
			freecopy(split_com);
		}
		else
			execve(command, &cmd->user_comm[0], envp);
		exit(0);
	}
	else
		wait(&status);
}
