#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#ifndef SIZE
#define SIZE 100
#endif

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	while (*s)
		ft_putchar(*(s++));
}

void	ft_putendl(char const *s)
{
	while (*s)
		ft_putchar(*(s++));
	ft_putchar('\n');
}

int		ft_strequ(char const *s1, char const *s2)
{
	int	equal;

	equal = strcmp(s1, s2);
	if (equal == 0)
		return (1);
	return (0);
}

void	ft_read_line(int fd, char *s)
{
	char	line[SIZE];
	char	*list[SIZE];
	int		i;
	ssize_t	retval;

	memset(line, 0, SIZE);
	memset(list, 0, SIZE * sizeof(*list));
	i = 0;
	ft_putstr("> ");
	while ((retval = read(1, line, SIZE)) > 0)
	{
		ft_putstr("> ");
		if (!strncmp(line, s, strlen(line) - 1))
			break ;
		else
			list[i++] = strdup(line);
		memset(line, 0, SIZE);
	}
	if (retval == 0)
		ft_putendl("21sh: warning: here-document delimited by end-of-file");
	i = -1;
	while (list[++i])
		write(fd, list[i], strlen(list[i]));
}

int		ft_get_double_less_than_pos(char **cmd)
{
	int	i;

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

int		ft_manage_double_less_than(char **cmd)
{
	char	*delimiter;
	int		less_than_pos;
	int		fd[2];
	pid_t	pid;
	int status;

	less_than_pos = ft_get_double_less_than_pos(cmd);
	delimiter = cmd[less_than_pos + 1];
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		// ft_read_line(fd[1], delimiter);
		close(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		ft_read_line(fd[1], delimiter);
		close(fd[1]);
		wait(&status);
		if (status > 0)
			exit(1);
	}
	// close(fd[1]);
	if (cmd[less_than_pos + 2] != NULL && cmd[less_than_pos + 3] != NULL)
		ft_open_file_fd(less_than_pos, cmd);
	return (less_than_pos);
}

int main()
{
	
	return 0;
}