/*
 * echo_server_tcp.c
 *
 *  Created on: 2018年4月8日
 *  Author: panda1949
 *  brief:我根据自己对linux网络编程的理解，所写的一个echo服务器采用tcp方式
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

int main(void)
{
	int serverfd,connfd,ret;
	struct sockaddr_in serveraddr,clientaddr;
	socklen_t len;
	char ip[40] = {0};
	char read_buff[256];

	//创建socket套接字IPV4 TCP
	serverfd = socket(AF_INET,SOCK_STREAM,0);
	if(serverfd < 0)
	{
		perror("socket create failed\n");
		exit(-1);
	}

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6666);
	inet_pton(AF_INET,SERVERIP,&serveraddr.sin_addr);
	//绑定
	ret = bind(serverfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret < 0)
	{
		close(serverfd);
		perror("bind failed\n");
		exit(-1);
	}

	//被动监听
	ret = listen(serverfd,10);
	if(ret < 0)
	{
		close(serverfd);
		perror("listen failed\n");
		exit(-1);
	}
	printf("listening...\n");

	len = sizeof(clientaddr);
	bzero(&clientaddr,sizeof(clientaddr));
	while(1)
	{
		connfd = accept(serverfd,(struct sockaddr*)&clientaddr,&len);//accept会阻塞，等待client接入
		printf("%s连接到服务器\n",inet_ntop(AF_INET,&clientaddr.sin_addr,ip,sizeof(ip)));
		/*
		if(serverfd < 0)
		{
			printf("accept error\n");
			continue;
		}
		*/
		while((ret = read(connfd,read_buff,256)))
		{
			write(connfd,read_buff,256);
			bzero(read_buff,256);
		}
		if(ret == 0)
		{
			printf("客户端关闭\n");
		}
		else
		{
			printf("read error");
		}
		close(connfd);
	}

	close(serverfd);

	return 0;
}
