/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:28:38 by goisetsi          #+#    #+#             */
/*   Updated: 2016/12/13 16:15:21 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(const char *env, char **env_list)
{
	env += 1;
	while (*env_list)
	{
		if (ft_strncmp(env, *env_list, ft_strlen(env) - 1) == 0)
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
	freecopy(cmd->user_comm);
	free(cmd->get_line);
}

int	ft_term_off(struct termios *term)
{
	term->c_lflag |= (ECHO | ECHOE | ICANON);
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("ve", NULL), 1, ft_myputchar);
	return (1);
}

int	ft_term_on(struct termios *term)
{
	if (tgetent(NULL, getenv("TERM")) < 1)
		return (0);
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ECHO | ECHOE | ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("vi", NULL), 1, ft_myputchar);
	return (1);
}

void	ft_pro_cmd(t_cmd *cmd, t_env *envp, struct termios *t, t_stack *hist)
{
	if (cmd->user_comm != NULL)
	{
		if (ft_strequ(cmd->user_comm[0], "exit"))
		{
			free_envp(envp);
			free_cmd(cmd);
			ft_close_keyboard(t);
			exit(0);
		}
		// hist->size = hist->hist_count;
		ft_push(hist, ft_strdup(cmd->get_line));
		ft_term_off(t);
		ft_run_commands(cmd->user_comm, cmd->get_line, envp, *hist);
		ft_term_on(t);
	}
}
