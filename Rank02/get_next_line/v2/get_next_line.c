/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 08:38:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/01/17 09:33:15 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*stradd(char *str, char c)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(str);
	ret = (char *)malloc((len + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < len)
		ret[i] = str[i];
	if (str)
		free(str);
	ret[i++] = c;
	ret[i] = '\0';
	return (ret);
}

bool	init_buf(int fd, t_buf *buf)
{
	buf->fd = fd;
	buf->max = read(buf->fd, buf->data, BUFFER_SIZE);
	buf->pos = -1;
	return (buf->max >= 0);
}

char	read_buf(t_buf *buf)
{
	if (++(buf->pos) == buf->max)
	{
		buf->max = read(buf->fd, buf->data, BUFFER_SIZE);
		buf->pos = 0;
	}
	if (!buf->max)
		return (0);
	return (buf->data[buf->pos]);
}

char	*get_next_line(int fd)
{
	static t_buf	buf = {.fd = -1};
	char			*line;
	char			c;


	if (buf.fd != fd)
		if (!init_buf(fd, &buf))
			return (NULL);
	c = read_buf(&buf);
	line = 0;
	while (c)
	{
		line = stradd(line, c);
		if (c == '\n')
			return (line);
		c = read_buf(&buf);
	}
	return (line);
}
