#include "minishell.h"

int		ft_is_logical(char *line)
{
	char	**sp;
	int		i;

	i = 0;
	sp = SPLIT(line, ' ');
	while (sp[i])
	{
		if (ft_strequ(sp[i], "&&") || ft_strequ(sp[i], "||"))
		{
			freecopy(sp);
			return (1);
		}
		i++;
	}
	freecopy(sp);
	return (0);
}

void	ft_log_op(t_cmd *cmd, t_env *envp, struct termios *t, t_stack *hist)
{
	int		i;
	t_cmd	logic;

	i = 0;
	while (cmd->user_comm[i])
	{
		if (!ft_strequ(cmd->user_comm[i], "&&") && !ft_strequ(cmd->user_comm[i], "||"))
		{
			logic.get_line = cmd->user_comm[i];
			if (!ft_strequ(logic.get_line, "") && ft_spaces_tabs(logic.get_line))
			{
				logic.user_comm = SPLIT(logic.get_line, ' ');
				ft_pro_cmd(&logic, envp, t, hist);
				freecopy(logic.user_comm);
			}
		}
		i++;
	}
}