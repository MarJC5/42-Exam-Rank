/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:20:41 by jmartin           #+#    #+#             */
/*   Updated: 2021/11/30 19:20:45 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_inter(char *s1, char *s2)
{
	int	i;
	int	alphabet[256] = {0};

	i = -1;
	while (s2[++i])
	{
		if (alphabet[(int)s2[i]] == 0)
			alphabet[(int)s2[i]] += 1;
	}
	i = -1;
	while (s1[++i])
	{
		if (alphabet[(int)s1[i]] == 1)
		{
			alphabet[(int)s1[i]] += 1;
			write (1, &s1[i], 1);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
