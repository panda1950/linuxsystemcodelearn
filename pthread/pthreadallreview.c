/* *
 *回顾先前所有的线程函数
 *创建一个线程并与之连接
 *pthread_create()
 *pthread_exit()
 *pthread_self()
 *pthread_join()
  * */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
static void *threadFunc(void *arg)
{
	char *s = (char *)arg;
	printf("%s",s);
	return (void *) strlen(s);
}

int main()
{
	pthread_t ntid;
	void *res;
	int s;
	s = pthread_create(&ntid,NULL,threadFunc,"hello world!\n");
	if(s != 0)
	{
		perror("create new pthread failed\n");
		return -1;
	}
	
	printf("this message is from main function\n");
	s = pthread_join(ntid,&res);
	if(s !=0 )
	{
		perror("pthread_join() failed\n");
		return -2;
	}
	printf("thread return value is %ld\n",(long)res);
	
	exit(EXIT_SUCCESS);
}





