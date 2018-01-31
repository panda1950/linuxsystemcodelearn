#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void myfun(int signum)
{
	int i;
	i = 0;
	while( i < 10)
	{
		printf("process signal signum = %d\n",signum);
		sleep(1);
		i++;
	}
	return ;
}

int main()
{
	int i ;
	i =0;
	signal(14,myfun);
	printf("before alarm\n");	
	alarm(9);
	printf("after alarm\n");
	while( i < 20)
	{
		i++;
		sleep(1);
		printf("process do  i = %d\n",i);
	}
	return 0;
}


