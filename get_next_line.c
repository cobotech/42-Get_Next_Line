/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykomori <ykomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:14:34 by ykomori           #+#    #+#             */
/*   Updated: 2026/10/19 12:23:41 by ykomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*chunk;
	int		bytes_read;

	chunk = malloc(BUFFER_SIZE + 1);
	bytes_read = read(fd, chunk, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(chunk);
		return (NULL);
	}
	chunk[bytes_read] = '\0';
	return (chunk);
}
