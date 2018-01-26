#include <stdio.h>
#include "pthread.h"

int thread_int = 0;

void *fun(void *var) //child thread code
{
	int j;
	while(thread_int == 0);
	for(j=0; j<10; j++)
	{
		usleep(100);
		printf("this is fun j = %d\n",j);
	}

}

int main()	//main thread code
{
	int i;
	char str[] = "hello linux\n";
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,fun,(void*)str);
	if(ret < 0)
	{
		perror("create thread failed\n");
		return -1;
	}
	for(i = 0; i < 10; i++)
	{
		usleep(100);
		printf("this is main fun i=%d \n",i);
	}
	thread_int = 1;
	while(1);
	return 0;
}





