#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
struct msgbuf
{
	long type;
	char voltage[128];
	char ID[4];
};



int main()
{
	int msgid;
	int readret;
	struct msgbuf sendbuf,recvbuf;

	msgid = msgget(IPC_PRIVATE,0777);
	if(msgid < 0)
	{
		perror("creat message failed\n");
		return -1;
	}
	printf("create message queue success msgid = %d\n",msgid);
	system("ipcs -q");

	sendbuf.type = 100;
	printf("please enter msg:\n");
	fgets(sendbuf.voltage,124,stdin);
	msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);

	memset(recvbuf.voltage,0,124); 

	readret = msgrcv(msgid,(void *)&recvbuf,124,100,0);
	printf("recv: %s\n readret = %d\n",recvbuf.voltage,readret);

	msgctl(msgid,IPC_RMID,NULL);
	system("ipcs -q");

	return 0;
}

