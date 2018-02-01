//this file achieve process communication of parent to child by share memory

#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
void myfun(int signum)
{
	return ;
}

int main()
{	
	int shmid;
	pid_t pid;
	char *ptr_map;
	//creat share memory
	shmid = shmget(IPC_PRIVATE,128,0777);
	if(shmid < 0)
	{
		perror("share memory create failed\n");
		return -1;
	}
	printf("share memory create success the shmid = %d \n",shmid);


	//create process
	pid = fork();
	if(pid > 0)
	{
		signal(SIGUSR2,myfun);
		//parent map share memory
		ptr_map = (char *)shmat(shmid,NULL,0);
		if(ptr_map == NULL)
		{
			perror("parent map share memory failed\n");
			return -2;
		}
		printf("this is parent process\n");
		sleep(1);
		//parent process write share memory
		while(1)
		{
			printf("parent process write share mem: \n");
			fgets(ptr_map,128,stdin);
			kill(pid,SIGUSR1); //send signal child read data
			pause();
		}
	}
	
	if(pid == 0)
	{

		//child map share memory
		ptr_map = (char *)shmat(shmid,NULL,0);
		if(ptr_map == NULL)
		{
			perror("child map share memory failed\n");
			return -2;
		}
		printf("this is child process\n");
		printf("child map success \n");
		
		signal(SIGUSR1,myfun);
		while(1)
		{
			pause(); //wait parent write
			printf("child read the share menm data :%s",ptr_map);
			kill(getppid(),SIGUSR2);
		}
	}


	


	return 0;
}

