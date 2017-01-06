/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 07:45:09 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/06 22:25:00 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(const char *env, char **env_list)
{
	int			index;
	const char	*ptr;

	if (*env != '$')
		return (NULL);
	env += 1;
	while (*env_list)
	{
		ptr = ft_strchr(*env_list, '=');
		index = ptr - *env_list;
		if (ft_strncmp(env, *env_list, index) == 0)
			return (*env_list + ft_strlen(env) + 1);
		env_list++;
	}
	return (NULL);
}

char	*ft_get_str(char **av)
{
	char	*ps;
	int		i;
	int		j;
	int		found;

	ps = av[2];
	i = 2;
	j = 3;
	found = 0;
	if (ft_start_with(av[2], '"'))
	{
		while (!ft_end_with(av[i], '"') && av[i])
			i++;
		if (ft_end_with(av[i], '"'))
			found = 1;
		while (j <= i && found)
		{
			ps = ft_strjoin(ps, " ");
			ps = ft_strjoin(ps, av[j]);
			j++;
		}
	}
	return (ps);
}

char	*ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->user_comm)
	{
		freecopy(cmd->user_comm);
		cmd->user_comm = NULL;
	}
	if (cmd->get_line)
	{
		free(cmd->get_line);
		cmd->get_line = NULL;
	}
	if (cmd->user_comm || cmd->get_line)
		free_cmd(cmd);
}

int		ft_pro_cmd(t_cmd *cmd, t_env *envp, struct termios *t, t_stack *hist)
{
	char	*tmp;

	tmp = ft_strdup(cmd->get_line);
	hist->counter = -1;
	ft_str_substitution(&cmd->get_line, envp->list);
	if ((cmd->user_comm = ft_strsplit(cmd->get_line, ' ')) != NULL)
	{
		if (ft_strequ(cmd->user_comm[0], "exit"))
		{
			free_cmd(cmd);
			ft_free_hash_table(hist->hash);
			ft_close_keyboard(t);
			exit(0);
		}
		ft_push(hist, tmp);
		ft_term_off(t);
		if (ft_is_logical(cmd->get_line))
			ft_log_op(cmd, envp, t, hist);
		else
			hist->counter = ft_run_commands(cmd, envp, hist);
		ft_term_on(t);
	}
	freecopy(cmd->user_comm);
	return (hist->counter);
}
