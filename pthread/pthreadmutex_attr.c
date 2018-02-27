/*
 * 目前这段代码还有问题，出现问题为段错误
 *对互斥量的练习
 *设置了互斥量的属性
 *在本例中创建了一个带错误检测属性的互斥量
 *
 * */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static volatile int glob = 0;   /* "volatile" prevents compiler optimizations
                                   of arithmetic operations on 'glob' */

//加入互斥量
pthread_mutex_t mtx;
pthread_mutexattr_t mtxAttr;
static void *threadFunc(void *arg)              /* Loop 'arg' times incrementing 'glob' */
{
    int loops = *((int *) arg);
    int loc, j,s,type;
	
	s = pthread_mutexattr_init(&mtxAttr);
	if(s != 0 )
	{
		printf("phtread_mutexattr init failed\n");
		exit(1);
	}
	s = pthread_mutexattr_settype(&mtxAttr,PTHREAD_MUTEX_ERRORCHECK); //设置互斥量的属性
	
	if(s != 0 )
	{
		printf("phtread_mutex attr set failed\n");
		exit(1);
	}
	s = pthread_mutex_init(&mtx,&mtxAttr);
	if(s != 0 )
	{
		printf("phtread_mutex init failed\n");
		exit(1);
	}
    for (j = 0; j < loops; j++) 
    {
		s = pthread_mutex_lock(&mtx);
		if(s !=0)
		{
			printf("pthread_mutex_lock failed\n");
			exit(1);
		}
        loc = glob;
        loc++;
        glob = loc;

		s = pthread_mutex_unlock(&mtx);
		if(s !=0)
		{
			printf("pthread_mutex_unlock failed\n");
			exit(1);
		}
/*
		s = pthread_mutexattr_destory(&mtxAttr);
		if(s !=0)
		{
			printf("pthread_mutexattr_destory failed\n");
			exit(1);
		}
*/
    }
	
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    loops = atoi(argv[1]);

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
    {
		printf("pthread_create failed\n");
		exit(1);
	}
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
	{
		printf("pthread_create failed\n");
		exit(1);
	}        

    s = pthread_join(t1, NULL);
    if (s != 0)
	{
		printf("pthread_join failed\n");
	} 
    s = pthread_join(t2, NULL);
    if (s != 0)
	{   
		printf("pthread_join failed\n");
	} 

    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}

