/*
 * echo_client_tcp.c
 *
 *  Created on: 2018年4月8日
 *  Author: panda1949
 *  brief:我根据自己对linux网络编程的理解，所写的一个echo客户端采用tcp方式
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

#define SERVERIP		"192.168.22.128"


int main (int argc,char **argv)
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

	//填写服务器地址信息
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6666);
	inet_pton(AF_INET,SERVERIP,&serveraddr.sin_addr);

	//连接到服务器
	ret =connect(clientfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(ret != 0)
	{
		close(clientfd);
		perror("connet failed\n");
		exit(-1);
	}
	while(1)
	{
		bzero(&buff,sizeof(buff));
		scanf("%s",buff);
		write(clientfd,buff,sizeof(buff));
		bzero(&buff,sizeof(buff));
		read(clientfd,buff,sizeof(buff));
		printf("echo: %s\n",buff);
	}
	close(clientfd);

	return 0;
}
