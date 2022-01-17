#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

static char	*ft_strchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == (unsigned char)c)
			return (str + i);
	return (str);
}

static char	*ft_strdup(char *str)
{
	int	i;
	char *copy;

	i = -1;
	copy = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (str[++i])
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

static char	*ft_substr(char *str, int len)
{
	int	i;
	char *new;

	i = -1;
	new = malloc(len + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (++i < len)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char *new;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++j])
		new[i++] = s2[j];
	new[i] = '\0';
	return (new);
}

static char	*ft_line(char **save)
{
	int		i;
	char	*tmp;
	char	*ret;

	tmp = NULL;
	ret = NULL;
	i = 0;
	while ((*save)[i] != '\n' && (*save)[i])
		i++;
	if ((*save)[++i] == '\n')
		ret = ft_substr(*save, i);
	else if (ft_strchr(*save, '\0'))
	{
		if ((*save)[i] == '\0')
		{
			free(*save);
			*save = NULL;
			return (NULL);
		}
		ret = *save;
		*save = NULL;
		return (ret);
	}
	tmp = ft_strdup(*save + i);
	free(*save);
	*save = tmp;
	return (ret);
}

static char	*ft_read(char **save, char *buf, int fd)
{
	int	file;
	char *tmp;

	tmp = NULL;
	file = read(fd, buf, BUFFER_SIZE);
	while (file)
	{
		buf[file] = '\0';
		tmp = ft_strjoin(*save, buf);
		free(*save);
		*save = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
		file = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	buf = NULL;
	return (ft_line(save));
}

char	*get_next_line(int fd)
{
	static char	*save;
	char *buf;
	char *ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	ret = ft_read(&save, buf, fd);
	if (!ret)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	return (ret);
}
