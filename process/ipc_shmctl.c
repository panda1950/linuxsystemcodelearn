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
	char *p;
	int mdt;
	int key;
	key =ftok("./a.c",'b');
	if(key < 0)
	{
		printf("creat key failed\n");
		return -2;
	}
	shmid = shmget(key,128,IPC_CREAT |0777);
	if(shmid < 0)
	{
		perror("creat share memery failed\n");
		return -1;
	}
	printf("shmget id is %d\n",shmid);
	system("ipcs -m");
	
	p = (char *)shmat(shmid,NULL,0);
	if(p == NULL)
	{
		perror("shmat failed\n");
		return -3;
	}

	//write share memory
	fgets(p,32,stdin);
	//start read
	printf("share memory is %s\n",p);
	printf("second read share memory the data is %s\n",p);
	mdt = shmdt(p);
	if(mdt == -1)
	{
		perror("shmdt failed\n");
		return -4;
	}
	printf("shmdt success\n");

	//shmctl delete share memory
	shmctl(shmid,IPC_RMID,NULL);
	system("ipcs -m");


	return 0;
}






