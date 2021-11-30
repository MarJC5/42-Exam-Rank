#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

char	ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char *new;
	
	i = -1
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	new = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++i])
		new[i] = s2[++j];
	new[i] = '\0';
	return (new);
}

int	get_next_line(char **line)
{

}
