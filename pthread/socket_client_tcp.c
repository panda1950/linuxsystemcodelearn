/*
 * Name:socket_client.c
 * Author: panda1949
 * Date: 2018年3月7日
 * Copyright:
 * brief:Socket编程的客户端 TCP 流式socket
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXlINE		4096


int main(int argc, char **argv)
{
	int sockfd,n;
	char recvline[4096],sendline[4096];
	struct sockaddr_in servaddr;

	if(argc != 2)
	{
		printf("usage: ./client <ipaddress\n>");
		exit(0);
	}
	//创建socket
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("create socket error: %s(errno:%d)\n",strerror(errno),errno);
		exit(0);
	}
	//将ip地址转换为2进制
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s\n",argv[1]);
		exit(0);
	}
	//连接
	if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
	{
		printf("connect socket error: %s(errno:%d)\n",strerror(errno),errno);
		exit(0);
	}
	//从终端获取内容并发送
	printf("send message to server: \n");
	fgets(sendline,4096,stdin);
	if(send(sockfd,sendline,strlen(sendline),0) < 0)
	{
		printf("send message error: %s(errno:%d)\n",strerror(errno),errno);
		exit(0);
	}
	close(sockfd);

	exit(0);

}

