/* Created on: 2018年1月26日
 * Author: panda1949
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	int fd,i;
	int process_com = 0;
	fd=open("./myfifo",O_RDONLY);
	if(fd < 0)
	{
		printf("open myfifo failed\n");
		return -1;
	}
	printf("open myfifo success");
	
	read(fd,&process_com,1);
	while(process_com == 0);

	for(i = 0; i <5; i++)	
	{
		printf("this is first process i= %d\n",i);
		usleep(100);
	}
	while(1);	

	return 0;
}
