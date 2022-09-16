#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void	ft_putstr_err(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	write(2, str, i);
}

int	ft_exec(char **argv, int i, int tmp_fd, char **env)
{
	argv[i] = NULL;
	execve(argv[0], argv, env);
	ft_putstr_err("error: cannot execute");
	ft_putstr_err(argv[0]);
	write(2, "\n", 1);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int i = 0;
	int tmp_fd = dup(STDIN_FILENO);
	int fd[2];
	int pid = 0;

	(void) argc;
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 0)
				ft_pustr_err("error: cd: bad arguments");
			else if (chdir(argv[1] != 0))
			{
				ft_putstr_err("error: cd: cannot execute");
				ft_putstr_err("argv[1]");
				write(2, "\n", 1);
			}
		}
		else if (argv != &argv[i] && (argv[i] == NULL || strcmp(argv[i], ";") = 0))
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(tmp_fd, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[1]);
			}
		}
	}
}
