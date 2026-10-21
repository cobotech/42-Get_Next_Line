/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykomori <ykomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:14:34 by ykomori           #+#    #+#             */
/*   Updated: 2026/10/21 09:06:04 by ykomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_leftover(int fd, char *leftover)
{
	char	*chunk;
	int		bytes_read;

	chunk = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (chunk == NULL)
	{
		free(leftover);
		return (NULL);
	}
	while (gnl_find_newline(leftover) == NULL)
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		else if (bytes_read < 0)
		{
			free(chunk);
			free(leftover);
			return (NULL);
		}
		chunk[bytes_read] = '\0';
		leftover = gnl_strjoin(leftover, chunk);
	}
	free(chunk);
	return (leftover);
}

static char	*extract_line(char *leftover)
{
	char	*line;
	size_t	len;

	len = 0;
	while (leftover[len] != '\0' && leftover[len] != '\n')
		len++;
	if (leftover[len] == '\n')
		len++;
	line = gnl_substr(leftover, 0, len);
	return (line);
}

static char	*update_leftover(char *leftover)
{
	size_t	len;
	char	*new_leftover;

	len = 0;
	while (leftover[len] != '\0' && leftover[len] != '\n')
		len++;
	if (leftover[len] == '\n')
		len++;
	if (gnl_strlen(leftover) - len == 0)
	{
		free(leftover);
		return (NULL);
	}
	new_leftover = gnl_substr(leftover, len, (gnl_strlen(leftover) - len));
	free(leftover);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = read_to_leftover(fd, leftover);
	if (leftover == NULL)
		return (NULL);
	line = extract_line(leftover);
	if (line == NULL)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	leftover = update_leftover(leftover);
	return (line);
}
