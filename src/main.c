/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:26:38 by goisetsi          #+#    #+#             */
/*   Updated: 2016/12/20 09:10:42 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_search_command(char *command)
{
	static char	*cmd = "echo pwd cd history setenv unsetenv env exit clear";
	char		**comm_split;
	int			i;

	i = 0;
	if (EQUAL(command, "export") || EQUAL(command, "unset"))
		return (1);
	comm_split = ft_strsplit(cmd, ' ');
	while (comm_split[i])
	{
		if (ft_strcmp(comm_split[i], command) == 0)
		{
			freecopy(comm_split);
			return (1);
		}
		i++;
	}
	freecopy(comm_split);
	return (0);
}

void	ft_execute_commands(char **cmd, char *line, t_env *envp, t_stack hist)
{
	char *dir;

	if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd, envp);
	else if (ft_strequ(cmd[0], "pwd"))
	{
		dir = ft_pwd();
		ft_putendl(dir);
		free(dir);
	}
	else if (ft_strequ(cmd[0], "export"))
		ft_export(cmd, envp);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(line, envp->list);
	else if (ft_strequ(cmd[0], "env"))
		ft_print_env(envp);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_set_envir(envp, line);
	else if (ft_strequ(cmd[0], "unsetenv") || ft_strequ(cmd[0], "unset"))
		ft_unsetting_env(line, envp);
	else if (ft_strequ(cmd[0], "history"))
		ft_display_hist(&hist, cmd, 0);
	else if (ft_strequ(cmd[0], "clear"))
		tputs(tgetstr("cl", NULL), 1, ft_myputchar);
}

void	ft_run_commands(char **user_comm, char *line, t_env *envp, t_stack hist)
{
	ft_advanced_com(user_comm, line, envp, hist);
}

char	*ft_build_comm(t_stack *hist, char *comm, char *buf, int pos)
{
	while (42)
	{
		hist->ret = read(0, buf, 4);
		buf[hist->ret] = '\0';
		if (buf[hist->ret - 1] == '\n')
			if (ft_enter_key(&comm, &pos, hist))
				break ;
		if (buf[0] == '\t')
			ft_autocomplete(&comm, &pos, hist->envp);
		else if (buf[0] == 4 && ft_strequ(comm, ""))
			return (ft_strdup("exit"));
		else if (ft_is_copy_n_paste(buf))
			ft_copy_n_paste(&comm, buf, &pos, hist);
		else if (ft_is_inter(buf) || ft_up_down(buf))
			ft_intermidiate(&comm, &pos, hist, buf);
		else if (ft_enter_and_edit_keys(buf, &pos, comm, hist))
			;
		else if (ft_navigation_keys(buf, &pos, comm))
			ft_cursor(comm, pos + 1, hist);
		else if (ft_character_keys(buf) && buf[0] != 27)
			ft_process_buff(&comm, pos++, buf[0], hist);
		ft_cursor(comm, pos + 1, hist);
	}
	return (comm);
}

int		main(int ac, char **av, char **envp)
{
	struct termios	term;
	t_stack			hist;
	t_cmd			cmd;
	t_env			*envp_copy;

	ft_create_stack(&hist, envp);
	envp_copy = copy_envp(4096, envp);
	ft_init_keyboard(&term, &ac, &av);
	signal(SIGINT, ft_ctrl_c_signal_handler);
	while (42)
	{
		prompt(&cmd, &hist);
		ft_complete_cmd(&cmd, &term);
		ft_putchar('\n');
		if (!ft_strequ(cmd.get_line, "") && ft_spaces_tabs(cmd.get_line))
		{
			ft_pro_cmd(&cmd, envp_copy, &term, &hist);
			free_cmd(&cmd);
		}
	}
	return (0);
}
