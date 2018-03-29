/**
 *name:		echo_client
 *author:	zhouwei
 *date:		2018.3.29
 *version:	v1.0
 *copyright: none
 *brief:	基于TCP通信的echo服务器的 客户端
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVERIP 	"192.168.1.118"

int main(int argc, char **argv)
{
	int clientfd,ret;
	struct sockaddr_in serveraddr;
	char buff[256];

	//创建socket
	clientfd = socket(AF_INET,SOCK_STREAM,0);
	if(clientfd < 0)
	{
		perror("socket create failed\n");
		exit(-1);
	}
	else
	{
		printf("socket create success\n");
	}

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6666);
	inet_pton(AF_INET,SERVERIP,&serveraddr.sin_addr);
	ret = connect(clientfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret != 0)
	{
		close(clientfd);
		printf("connet failed \n");
		exit(-1);
	}
	while(1)
	{
		bzero(buff,sizeof(buff));
		scanf("%s",buff);
		write(clientfd,buff,sizeof(buff)); //写数据
		bzero(buff,sizeof(buff));
		read(clientfd,buff,sizeof(buff));   //读数据
		printf("echo: %s\n",buff);
	}
	close(clientfd);
	return 0;
}



