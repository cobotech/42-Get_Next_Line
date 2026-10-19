#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"


int	main(void)
{
	int		fd;
	char * line;

	fd = open("test.txt", O_RDONLY);
	line= get_next_line(fd);


	while(line!=NULL){
		printf("[%s]\n", line);
		free(line);
		line= get_next_line(fd);
	}


	/*
	たとえ:おかしの箱
get_next_line は、毎回 新しいおかしの箱 をくれる人です(malloc した箱)
line は、いま手に持っている箱を指さしている指 です
free(line) は、指さしている箱を ゴミ箱に捨てる ことです

	*/
	return (0);
}
