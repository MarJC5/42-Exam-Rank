#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*result;

	i = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		result = get_next_line(fd);
		while (i++ < 30)
		{
			printf("%s", result);
			result = get_next_line(fd);
		}
	}
	return (0);
}
