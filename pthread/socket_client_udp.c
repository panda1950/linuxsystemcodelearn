/* *
 *Name:Socket_client_udp.c
 *Author:周韦
 *Date:2018.3.7
 *Copyright:
 *Brief: UDP Client 编写socket编程，基于socket数据报 老方法
 * */


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXDATASIZE		100

int main(int argc, char **argv)
{
	int fd,numbytes;
	int sin_len = sizeof(struct sockaddr_in);
	char buff[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in serveraddr,reply;

	if(argc != 3)
	{
		printf("Usage: %s <IP Address> <message>\n",argv[0]);
		exit(1);
	}
	
//	if(getaddinfo(argv[1],PORT_NUM,&hints,&result) != 0)
	if((he = gethostbyname(argv[1])) == NULL)
	{
		printf("get infomation faild\n");
		exit(1);
	}
	
	//建立socket套接字
	if((fd = socket(AF_INET,SOCK_DGRAM,0)) == -1)
	{
		printf("create socket error: %s(errno: %d)",strerror(errno),errno);
		exit(1);
	}

	//绑定
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6666);
	serveraddr.sin_addr = *((struct in_addr *)he->h_addr);

	sendto(fd,argv[2],strlen(argv[2]),0,\
					(struct sockaddr *)&serveraddr,sizeof(struct sockaddr));

	while (1)   
    {  
	 /*接收来自服务器的消息*/
	if ((numbytes=recvfrom(fd,buff,MAXDATASIZE,0,\  
                        (struct sockaddr *)&reply,&sin_len)) == -1)  
	{
		perror("recvfrom()");   
		exit(1);
	}   
    if (sin_len == sizeof(struct sockaddr) && memcmp((const void *)&serveraddr, (const void *)&reply,sin_len) == 0)  
     {  
          printf("Receive message from server.\n");
		  buf[numbytes]='\0';  
          printf("Server Message: %s\n",buf);   
          break;  
	  }  
	 }
	close(fd);
	return 0;
}














