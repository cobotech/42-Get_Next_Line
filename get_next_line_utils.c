/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykomori <ykomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:25:49 by ykomori           #+#    #+#             */
/*   Updated: 2026/10/04 15:51:10 by ykomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

char *ft_substr(char const *s, unsigned int start, size_t len){

}

char *ft_strjoin(char const *s1, char const *s2){

}

size_t gnl_strlen(const char *stash){
	if (stash==NULL)
	return (0);

	size_t counter;
		counter = 0;
	while(stash[counter]!='\0'){
		counter+=1;
	}
	return(counter);
}
char * gnl_find_newline(const char *stash){
if (stash==NULL)
	return (NULL);

size_t counter;
		counter = 0;
	while(stash[counter]!='\0'){
		if(stash[counter]== '\n')
		return((char *)&stash[counter]);
		counter+=1;
	}
	return(NULL);

}
