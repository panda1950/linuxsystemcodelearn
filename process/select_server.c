/*
 * select_server.c
 *
 *  Created on: 2018年4月18日
 *  Author: zhouwei
 *  brief: 从博客学习select函数的使用,本文件实现一个服务器多个客户端，采用select函数实现
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>

#define BUF_SIZE		200

void error_handing(char* buf);

int main(int argc, char **argv)
{
	int serv_sock,clnt_sock;
	struct sockaddr_in serv_adr,clnt_adr;
	struct timeval timeout;
	fd_set reads,cpy_reads;

	socklen_t adr_sz;

	int fd_max,str_len,fd_num,i;
	char buf[BUF_SIZE];
	if(argc != 2)
	{
		printf("Usage: %s <port\n>",argv[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_port = htons(atoi(argv[1]));
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

	//绑定
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	        error_handing("bind() error");
	//监听
	 if(listen(serv_sock, 5) == -1)
	        error_handing("listen() error");

	 FD_ZERO(&reads);
	 FD_SET(serv_sock,&reads);//将服务器端套接字作为读监视对象
	 fd_max = serv_sock;

	 while(1)
	 {
		 cpy_reads = reads;
		 timeout.tv_sec = 5;
		 timeout.tv_usec = 5000;

		 //无限循环调用select 监视可读事件
		 if((fd_num = select(fd_max +1,&cpy_reads,0,0,&timeout)) == -1)
		 {
			 perror("select error\n");
			 exit(1);
		 }
		 if(fd_num == 0)//超时
		 {
			 continue;
		 }

		 for(i = 0; i < fd_max+1; i++)
		 {
			 if(FD_ISSET(i,&cpy_reads)) //检查服务器端套接字是否有变化
			 {
				 if(i == serv_sock)
				 {
					 adr_sz = sizeof(clnt_adr);
					 clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_adr,&adr_sz);
					 FD_SET(clnt_sock,&reads);  //把新接入的套接字加入监视
					 if(fd_max < clnt_sock)
					 {
						 fd_max = clnt_sock;
					 }
					 printf("conneted clinet: %d\n",clnt_sock);
				 }
				 else
				 {
					 str_len = read(i,buf,BUF_SIZE);
					 if(str_len == 0)
					 {
						 FD_CLR(i,&reads);
						 close(i);
						 printf("closed client: %d\n",i);
					 }
					 else
					 {
						 write(i,buf,str_len);//echo
					 }
				 }
			 }

		 }
	 }
	 close(serv_sock);
	 return 0;
}
void error_handing(char* buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
