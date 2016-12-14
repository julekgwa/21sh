#include "minishell.h"

void	ft_read_line(int fd, char *s)
{
    char line[SIZE];
    char *list[SIZE] = { 0 };
    int i = 0;
    ssize_t retval;
    memset(line, 0, SIZE);
    while ((retval = read(1, line, SIZE)) > 0)
   {
        
        if (!strncmp(line, s, strlen(line) - 1))
            break;
        else
            list[i++] = strdup(line);
        memset(line, 0, SIZE);
    }
    if (line[0] == 4)
    	ft_putendl("Yes");
    i = 0;
    while (list[i])
    {
        write(fd, list[i], strlen(list[i]));
        i++;
    }
}

int	ft_get_double_less_than_pos(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strequ(cmd[i], "<<"))
			return (i);
		i++;
	}
	return (0);
}

void	ft_open_file_fd(int pos, char **cmd)
{
	char	*file_name;
	int		fd;

	if (ft_strequ(cmd[pos + 2], ">"))
	{
		if (cmd[pos + 3] != NULL)
		{
			file_name = cmd[pos + 3];
			fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			dup2(fd, 1);
		}
	}
	else if (ft_strequ(cmd[pos + 2], ">>"))
	{
		if (cmd[pos + 3] != NULL)
		{
			file_name = cmd[pos + 3];
			fd = open(file_name, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			dup2(fd, 1);
		}
	}
}

int	ft_manage_double_less_than(char **cmd)
{
	char	*delimiter;
	int		less_than_pos;
	int		fd[2];

	less_than_pos = ft_get_double_less_than_pos(cmd);
	delimiter = cmd[less_than_pos + 1];
	pipe(fd);
	ft_read_line(fd[1], delimiter);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (cmd[less_than_pos + 2] != NULL && cmd[less_than_pos + 3] != NULL)
		ft_open_file_fd(less_than_pos, cmd);
	return (less_than_pos);
}