#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	int msgid;
	msgid = msgget(IPC_PRIVATE,0777);
	if(msgid < 0)
	{
		perror("creat message failed\n");
		return -1;
	}
	printf("create message queue success msgid = %d\n",msgid);
	system("ipcs -q");

	msgctl(msgid,IPC_RMID,NULL);
	system("ipcs -q");

	return 0;
}

