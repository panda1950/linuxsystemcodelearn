#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void myfun(int signum)
{
	int i = 0;
	i = 0;
	while(i < 5)
	{
		printf("receive signum =%d , i = %d\n",signum,i);
		sleep(1);
		i++;
	}
	
}

void myfun1(int signum)
{
	printf("receive signum =%d\n",signum);
	wait(NULL);
}


int main()
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		int i;
		i =0 ;
		signal(10,myfun);
		signal(17,myfun1);
		while(1)
		{
			printf("parent process  i= %d\n",i);
			sleep(1);
			i++;
		}	
	}
	if(pid  == 0)
	{
		sleep(10);
		kill(getppid(),10);
		sleep(10);
		exit(0); //kill SIGCHLD
	}
	return 0;
}

