/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 08:39:01 by jmartin           #+#    #+#             */
/*   Updated: 2022/01/17 09:25:59 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_but
{
	int fd;
	int max;
	int pos;
	char data[BUFFER_SIZE];
} t_buf;

char	*get_next_line(int fd);

#endif
