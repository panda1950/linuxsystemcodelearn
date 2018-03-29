/*******************************
 *	filename:echo_server
 *	author: zhouwei
 *	date:	2018.3.27
 * 	version: v1.0
 * 	brief:	一个简单的echo服务器的服务器端程序
 *			迭代型TCP方式echo服务器端程序
 * *****************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVERIP	"192.168.1.118"
int main(int argc, char **argv)
{
	int socketfd,ret,connfd;
	socklen_t len;
	char readbuff[256] = {0};
	char ip[40] = {0};
	struct sockaddr_in serveraddr; //定义一个socket地址类型结构体
	struct sockaddr_in clientaddr;

	//创建SOCKET
	socketfd = socket(AF_INET,SOCK_STREAM,0);
	if(socketfd < 0)
	{
		perror("socket create failed\n");
		exit(-1);
	}
	else
	{
		printf("socket create success\n");
	}

	memset(&serveraddr,0,sizeof(serveraddr)); //初始化清零结构体里面的内容
	serveraddr.sin_family = AF_INET;  //IPV4
	serveraddr.sin_port = htons(6666);	      //端口6666
//	serveraddr.sin.s_addr = htons(INADDR_ANY);
	inet_pton(AF_INET,SERVERIP,&serveraddr.sin_addr); //转为网络字节序

	//绑定
	ret = bind(socketfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret != 0)
	{
		close(socketfd);
		perror("bind failed\n");
		exit(-1);
	}
	else
	{
		printf("bind success\n");
	}

	//监听
	ret = listen(socketfd,5);
	if(ret !=0 )
	{
		close(socketfd);
		perror("listen failed\n");
		exit(-1);
	}
	else 
	{
		printf("listening....\n");
	}
	len = sizeof(clientaddr); 
	bzero(&clientaddr,sizeof(clientaddr));

	while(1)
	{
		connfd = accept(socketfd,(struct sockaddr *)&clientaddr,&len); //接受客户端连接
		printf("%s 连接到服务器\n",inet_ntop(AF_INET,&clientaddr.sin_addr,ip,sizeof(ip)));
		if(socketfd < 0)
		{
			printf("accept failed\n");
			continue;
		}
		while((ret = read(connfd,readbuff,256))) //读客户端发送的数据
		{
			write(connfd,readbuff,256);//写回客户端
			bzero(readbuff,256);
		}
		if(ret == 0)
		{
			printf("客户端关闭连接\n");
		}
		else
		{
			printf("read failed\n");
		}
		close(connfd);

	}
	close(socketfd);

	return 0;
}






