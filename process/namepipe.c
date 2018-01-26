#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
int main()
{
	int fd,i;
	char process_com = 0;
	fd = open("./myfifo",O_WRONLY);
	if(fd < 0)
	{
		perror("open myfifo failed\n");
		return -1;
	}
	printf("open myfifo success\n");
	for(i = 0; i <5; i++)	
	{
		printf("this is first process i= %d\n",i);
		usleep(100);
	}
	sleep(5);
	process_com = 1;
	write(fd,&process_com,1);
	while(1);	
		
			
	return 0;
}

