//this file achieve process communication of client to server by share memory

#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
struct mybuff
{
	int pid;
	char buff[124];
}

void myfun(int signum)
{
	return ;
}

int main()
{	
	int shmid;
	pid_t pid;
	struct mybuff  *ptr_map;
	//creat share memory
	int key;
	key = ftok("./b.c",'a');
	if(key < 0)
	{
		perror("key create failed\n");
		return -1;
	}
	printf("key create success\n");
	shmid = shmget(key,128,IPC_CREAT |0777);
	if(shmid < 0)
	{
		perror("share memory create failed\n");
		return -1;
	}
	printf("share memory create success the shmid = %d \n",shmid);

	
	signal(SIGUSR2,myfun);
	//server map share memory
	ptr_map = (struct shmbuf *)shmat(shmid,NULL,0);
	if(ptr_map == NULL)
	{
		perror("parent map share memory failed\n");
		return -2;
	}
	printf("this is parent process\n");
	sleep(1);

	//get client pid
	ptr_map->pid = getpid(); //write pid to share memory
	
	pause(); //wait client read pid

	pid = ptr_map->pid;

	//parent process write share memory
	while(1)
	{
		printf("parent process write share mem: \n");
		fgets(ptr_map->buf,128,stdin);
		kill(pid,SIGUSR1); //send signal child read data
		pause();
	}
	
	

	


	return 0;
}

