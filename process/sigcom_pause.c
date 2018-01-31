#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
int main()
{
	int i ;
	i =0;
	printf("before alarm\n");	
	pause();
	printf("after alarm\n");
	while( i < 20)
	{
		i++;
		sleep(1);
		printf("process do \n");
	}
	return 0;
}


