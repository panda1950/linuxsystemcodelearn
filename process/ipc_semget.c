#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/ipc.h>


int main()
{

	int semid;
	semid = semget(IPC_PRIVATE,3,0777);
	if(semid < 0)
	{
		printf("create semaphore failed\n");
		exit(1);
	}
	
	printf("create semaphore success the semid is %d\n",semid);
	
	system("ipc - s");
	
	while(1);
//	semctl();
	
	return 0;

}

