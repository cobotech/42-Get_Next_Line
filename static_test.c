#include <stdio.h>

int count_up(void){
	static int count ;
	count +=1;
	return(count);
}

int main  (void){
	printf("%d\n",count_up());
	printf("%d\n",count_up());
	printf("%d\n",count_up());
	return(0);
}
