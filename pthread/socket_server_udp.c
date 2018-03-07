/*
 * socket_server_udp.c
 * Author: panda1949
 * Date: 2018年3月7日
 * Copyright:
 * brief:UDP Server 基于数据报的服务器端
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define  MAXDATASIZE		100


int main()
{
	int sockfd;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	socklen_t sin_size;
	int num,len;
	char feedback[] = "welcome my server\n";

	//接收缓冲区
	char message[MAXDATASIZE];

	//创建UDP套接字
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1)
	{
		printf("create socket error: %s(errno: %d)",strerror(errno),errno);
		exit(1);
	}
	//绑定
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6666);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if( (bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) ) == -1)
	{
		printf("bind socket error: %s(errno: %d)",strerror(errno),errno);
		exit(1);
	}

	sin_size = sizeof(struct sockaddr_in);
	len = sizeof(struct sockaddr_in);

	printf("============message received zoom========== \n");
	while(1)
	{
		num = recvfrom(sockfd,message,MAXDATASIZE,0,\
				(struct sockaddr *)&clientaddr,&sin_size);
		if(num < 0)
		{
			perror("recvfrom error\n");
			exit(1);
		}

		message[num] = '\n';
//		if(inet_ntop((AF_INET,&clientaddr.sin_addr),message,INET_ADDRSTRLEN) == NULL )
		if(inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,message,INET_ADDRSTRLEN))
		{
			printf("convert client address failed \n");
			exit(1);
		}
		printf("The received message from:  %s\n the message is %s \n",ntohs(clientaddr.sin_addr.s_addr),message);
		//向客户端发送回馈信息
		sendto(sockfd,feedback,num,0,
				(struct sockaddr *)&clientaddr,len);
		//如果消息是退出则关闭服务器
		if(!strcmp(message,"quit"))
			break;
	}

	//关闭套接字
	close(sockfd);
	return 0;

}








