/*
 *Name: socket_server.c
 *Author: panda1949
 *Date: 2018年3月7日
 * Copyright:
 * brief: socket编程的服务器端 TCP 流式socket
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE		4096

int main(int argc,char **argv)
{
	int listenfd,connfd;
	struct sockaddr_in servaddr,clientaddr;
	socklen_t length = sizeof(clientaddr);
	char buff[4096];
	int n;

	//创建socket
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printf("create socket error: %s(errno: %d)",strerror(errno),errno);
		exit(0);
	}

	//绑定地址和端口
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6666);

	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
	{
		printf("bind socket error: %s(errno: %d)",strerror(errno),errno);
		exit(0);
	}

	//标记为被动，监听接入连接
	if(listen(listenfd,10) == -1)
	{
		printf("listen socket error: %s(errno: %d)",strerror(errno),errno);
		exit(0);
	}

	printf("=====waiting for client request===\n");
	while(1)
	{
		if((connfd = accept(listenfd,(struct sockaddr *)&clientaddr,&length)) == -1)
		{
			printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
			continue;
		}

		n = recv(connfd,buff,MAXLINE,0);
		buff[n] = '\0';
		printf("reccived message from client is: %s\n",buff);
		close(connfd);

	}
	close(listenfd);

	return 0;
}
