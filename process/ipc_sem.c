#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


int main()
{
	int semid;
	//create semaphore
	semid = semget(IPC_PRIVATE,3,0777);
	if(semid < 0)
	{
		perror("creat semaphore failed\n");
		return -1;
	}
	printf("create semaphore success msgid = %d\n",semid);
	system("ipcs -s");


	semctl(semid,0,IPC_RMID);
	system("ipcs -s");
	return 0;
}

