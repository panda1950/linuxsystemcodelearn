#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void print_id(char *s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	
	printf("%s pid is %u, tid is %u",pid,tid);
}

void *pthread_fun(void *arg)
{
	print_id(arg);
	return (void *)0;
}


int main()
{
	pthread_t ntid;
	int err;

	err = pthread_create(&ntid,NULL,pthread_fun,"newthread");
	if(err != 0)
	{
		perror("create new pthread failed\n");
		return -1;
	}

	print_id("main thread is :");
	sleep(2);

	return 0;
}


