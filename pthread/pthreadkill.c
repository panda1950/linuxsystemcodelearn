
//这个有问题需要重新修改
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void *thread_fun(void *arg)
{
	printf("this is new thread\n");


	return ((void *)0);
}



int main()
{
	pthread_t tid;
	int err;
	int s;

	err = pthread_create(&tid,NULL,thread_fun,NULL);
	if(err != 0)
	{
		printf("create pthread failed\n");
		exit(1);
	}
	printf("create pthread success\n");
	sleep(1);

	s = pthread_kill(tid,0);
	if(s == 'ESRCH')
	{
		printf("the thread is not found\n");
	}

	return 0;
}


