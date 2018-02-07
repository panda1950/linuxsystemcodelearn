#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_fun1(void *arg)
{
	printf("i am thread 1\n");
	return ((void *)1);

}

void *thread_fun2(void *arg)
{
	printf("i am thread 2\n");
	pthread_detach(pthread_self()); //分离自己
	return ((void *)2);
}

int main(int argc, char *argv[])
{
	int err1,err2;
	pthread_t tid1,tid2;
	void * pretval1;
	void * pretval2;
	int retval1,retval2;
	err1 =pthread_create(&tid1,NULL,thread_fun1,NULL);
	err2 =pthread_create(&tid2,NULL,thread_fun2,NULL);
	if(err1 != 0)
	{
		perror("create new pthread1 failed\n");
		exit(0);
	}
	if(err2 != 0)
	{
		perror("create new pthread2 failed\n");
		exit(0);
	}

	sleep(1);
	printf("main thread\n");
	retval1 = pthread_join(tid1,&pretval1);
	retval2 = pthread_join(tid2,&pretval2);

	printf("tid1 join retval is %d tid2 join retval is %d\n",retval1,retval2);
	printf("thread1 exit code is %d \n",((int*)pretval1));
	printf("thread1 exit code is %d \n",((int*)pretval2));
	return 0;
}



