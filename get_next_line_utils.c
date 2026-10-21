/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykomori <ykomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:25:49 by ykomori           #+#    #+#             */
/*   Updated: 2026/10/21 09:08:56 by ykomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*strings;
	size_t	i;

	strings = (char *)malloc(sizeof(char) * (len + 1));
	if (strings == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		strings[i] = s[start + i];
		i++;
	}
	strings[len] = '\0';
	return (strings);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*strings;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	strings = (char *)malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (strings == NULL)
	{
		free(s1);
		return (NULL);
	}
	while ((s1 && s1[i]))
	{
		strings[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strings[i + j] = s2[j];
		j++;
	}
	strings[i + j] = '\0';
	free(s1);
	return (strings);
}

size_t	gnl_strlen(const char *s)
{
	size_t	counter;

	if (s == NULL)
		return (0);
	counter = 0;
	while (s[counter] != '\0')
	{
		counter += 1;
	}
	return (counter);
}

char	*gnl_find_newline(const char *stash)
{
	size_t	counter;

	if (stash == NULL)
		return (NULL);
	counter = 0;
	while (stash[counter] != '\0')
	{
		if (stash[counter] == '\n')
			return ((char *)&stash[counter]);
		counter += 1;
	}
	return (NULL);
}
