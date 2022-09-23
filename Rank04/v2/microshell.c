#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>

void print_err(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    write(2, str, i);
}

int main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		return (0);

	int count = 1;
	for (int i = 0; argv[i]; i++)
	{
		if (!strcmp(argv[i], "|") || !strcmp(argv[i], ";"))
		{
			count++;
			while (!strcmp(argv[i], ";"))
				i++;
			if (!strcmp(argv[i - 1], ";"))
				i--;
		}
	}

	bool type[count];
	int pos[count];

	for (int i = 0; i < count; i++)
		type[i] = 0;
	pos[0] = 1;

	int j = 0;
	for (int i = 0; argv[i]; i++)
	{
		if (!strcmp(argv[i], "|"))
		{
			pos[j + 1] = i + 1;
			type[j++] = 1;
			argv[i] = NULL;
		}
		else if (!strcmp(argv[i], ";"))
		{
			while (!strcmp(argv[i], ";"))
				argv[i++] = NULL;
			pos[1 + j++] = i;
		}
	}

	int fd[2];
	int fdd = 0;
	int pid;

	for (int i = 0; i < count; i++)
	{
		if (!strcmp(argv[pos[i]], "cd"))
		{
			if (argv[pos[i] + 2])
			{
				print_err("error: cd: bad arguments\n");
				return (1);
			}
			else if (chdir(argv[pos[i] + 1]))
			{
				print_err("error: cd: cannot change directory to ");
				print_err(argv[pos[i] + 1]);
				print_err("\n");
			}
		}
		else
		{
			if (pipe(fd) == -1)
			{
				print_err("error: fatal\n");
				exit(1);
			}
			if ((pid = fork()) == -1)
			{
				print_err("error: fatal\n");
				exit(1);
			}
			if (!pid)
			{
				dup2(fdd, 0);
				if (type[i] == 1)
					dup2(fd[1], 1);
				if (execve(argv[pos[i]], &argv[pos[i]], envp) == -1)
				{
					print_err("error: cannot execute ");
					print_err(argv[pos[i]]);
					print_err("\n");
				}
			}
			else
			{
				waitpid(pid, NULL, 0);
				close(fd[1]);
				close(fdd);
				fdd = fd[0];
			}
		}
	}
	return (0);
}
