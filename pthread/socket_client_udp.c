/*
 * socket_server_udp.c
 * Author: panda1949
 * Date: 2018年3月8日
 * Copyright:
 * brief:UDP Client 基于数据报的客户端
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define  MAXDATASIZE		100

int main(int argc ,char **argv)
{
	int sockfd,numbytes;
	//服务器的地址信息
	struct sockaddr_in server,reply;
	char buff[MAXDATASIZE];
	//存储远程服务器信息
	struct hostent *he;

	socklen_t sin_len;
	sin_len = sizeof(struct sockaddr_in);

	//提示如何使用客户端
	if(argc != 3)
	{
		printf("Usage: %s <IP Address> <message>\n",argv[0]);
		exit(1);
	}

	if((he = gethostbyname(argv[1])) == NULL)
	{
		printf("gethostbyname failed\n");
		exit(1);
	}

	//创建socket
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1)
	{
		printf("create socket error: %s(errno: %d)",strerror(errno),errno);
		exit(1);
	}
	else
	{
		printf("socket create success\n");
	}

	//设置服务器地址和端口信息
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(6666);
	server.sin_addr = *((struct in_addr*)he->h_addr);

	//发送UDP消息到服务器
	sendto(sockfd,argv[2],strlen(argv[2]),0,(struct sockaddr *)&server,sizeof(struct sockaddr));

	while(1)
	{
		//接收来自服务器的信息
		if((numbytes = recvfrom(sockfd,buff,MAXDATASIZE,0,(struct sockaddr *)&reply,&sin_len)) == -1)
		{
			perror("recvfrom failed\n");
			exit(1);
		}

		if((sin_len == sizeof(struct sockaddr) && \
				memcmp( (const void*)&server,(const void*)&reply,sin_len)) == 0)
		{
			printf("Received message from server \n");
			buff[numbytes] = '\0';
			printf("server message is %s",buff);
			break;
		}
	}

	//关闭套接字
	close(sockfd);
	return 0;
}











