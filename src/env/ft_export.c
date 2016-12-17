#include "minishell.h"

void	ft_export(char **cmd, t_env *envp)
{
	char	*name;
	char	**split;
	char	**r;

	if (cmd[1][0] == '=')
	{
		ft_putstr("21sh: export: `");
		ft_putstr(cmd[1]);
		ft_putendl("': not a valid identifier");
		return ;
	}
	if (cmd[1] && CONTAINS(cmd[1], '='))
	{
		split = ft_strsplit(cmd[1], '=');
		name = split[0];
		r = NULL;
		ft_unsetenv(name, envp, r);
		ft_push_env(envp, cmd[1]);
		freecopy(split);
	}
}