/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:57:22 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/08 10:29:01 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

int	free_all(char *str, char **drawing, FILE *file)
{
	if (drawing)
		free(drawing);
	if (file)
		fclose(file);
	return (str_error(str));
}

int	main(int argc, char **argv)
{
	FILE 	*file;
	int		width;
	int		height;
	char	background;
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
	char	**drawing;
	int		i = 0;
	int		j = 0;
	int		ret_scanf;

	if (argc != 2)
		return (str_error("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file currupted"));
	if ((ret_scanf = fscanf(file, "%d %d %c\n", &width, &height, &background)) != 3)
		return (free_all("Error: Operation file corrupted\n", NULL, file));
	if (width <= 0 || height <= 0 || width > 300 || height > 300)
		return (free_all("Error: Operation file corrupted\n", NULL, file));

	drawing = malloc(sizeof(char *) * height);

	while (i < width)
	{
		drawing[i] = malloc(sizeof(char) * width);
		i++;
	}
	i = 0;
	while (i < height)
	{
		while (j < width)
		{
			drawing[i][j] = background;
			j++;
		}
		j = 0;
		i++;
	}

	while ((ret_scanf = fscanf(file, "%c %f %f %f %c\n", &type, &x, &y, &radius, &color)) == 5)
	{
		if ((type != 'C' && type != 'c') || radius <= 0)
			return (free_all("Error: Operation file corrupted\n", drawing, file));
		if (type == 'C')
		{
			i = 0;
			j = 0;
			while (i < height)
			{
				while (j < width)
				{
					if (sqrt(((x - j) * (x - j)) + ((y - i) * (y - i))) <= radius)
						drawing[i][j] = color;
					j++;
				}
				j = 0;
				i++;
			}
			if (type == 'c')
			{
				i = 0;
				j = 0;
				while (i < height)
				{
					while (j < width)
					{
						if (sqrt(((x - j) * (x - j)) + ((y - i) * (y - i))) <= radius)
							if (sqrt(((x - j) * (x - j)) + ((y - i) * (y - i))) > radius - 1)
								drawing[i][j] = color;
						j++;
					}
					j = 0;
					i++;
				}
			}
		}
	}

	if (ret_scanf != -1)
		return (free_all("Error: Operation file corrupted\n", drawing, file));

	i = 0;
	j = 0;
	while (i < height)
	{
		while (j < width)
		{
			write(1, &drawing[i][j], 1);
			j++;
		}
		j = 0;
		i++;
		write(1, "\n", 1);
	}

	free_all(NULL, drawing, file);

	return (0);
}
