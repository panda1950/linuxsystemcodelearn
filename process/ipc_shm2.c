#include <sys/types.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
int main()
{
	int shmid;
	int key;
	key = ftok("./a.c",'a');
	if(key <0)
	{
		printf("create key failed");
		return -1;
	}
	printf("create key success key = %d\n",key);

	shmid = shmget(key,128,777);
	if(shmid < 0)
	{
		perror("creat share memery failed\n");
		return -1;
	}
	printf("shmget id is %d\n",shmid);
	system("ipcs -m");
	system("ipcrm -m shmid");
	return 0;
}






