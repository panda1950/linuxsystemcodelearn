#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	pid = fork();
	int process_inter = 0;
	if(pid == 0)	//second
	{
		int i = 0;
		while(process_inter == 0);
		for(i = 0; i < 5; i++)
		{
			printf("this is child process i=%d\n ",i);
			usleep(100);
		}
	}

	if(pid > 0)  //first
	{
		
		int i = 0;
		for(i = 0; i < 5; i++)
		{
			printf("this is parent process i=%d\n ",i);
			usleep(100);
		}
		process_inter = 1;
	}

	while(1);




















	return 0;
}





