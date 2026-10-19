/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykomori <ykomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:16:39 by ykomori           #+#    #+#             */
/*   Updated: 2026/10/17 02:54:09 by ykomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
char *get_next_line(int fd);
char *gnl_substr(char const *s, unsigned int start, size_t len);
char *gnl_strjoin(char  *s1, char const *s2);
size_t gnl_strlen(const char *stash);
char * gnl_find_newline(const char *stash);
#endif
