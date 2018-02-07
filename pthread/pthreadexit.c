#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_fun(void *arg)
{
	int n;
	n = atoi(arg);
	if(n == 1)
	{	printf("new thread return 1 \n");
		return( (void*) 1);
	}

	if(n == 2)
	{	printf("pthread exit 2 \n");
		pthread_exit((void *)2);
	}

	if(n == 3)
	{	printf("exit fun 3 \n");
		exit(3);
	}
}


int main(int argc, char *argv[])
{
	int err;
	pthread_t tid;
	
	err =pthread_create(&tid,NULL,thread_fun,(void *)argv[1]);
	if(err != 0)
	{
		perror("create new pthread failed\n");
		exit(0);
	}
	sleep(1);
	printf("main thread\n");
	return 0;
}



