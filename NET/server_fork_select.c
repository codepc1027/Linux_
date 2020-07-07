/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：server_fork.c
*   创 建 者：pc
*   创建日期：2020年07月02日
*   描    述：可以接受多个客户端连接的服务器（fork）
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int create_server_listenfd()
{
	int listenfd;
	int ret;
	int opt = 1;
	//create listenfd
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd < 0)
	{
		perror("listenfd create failure!\n");
		return -1;
	}
	printf("create listenfd success!\n");
	//addr reuse
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	//bind
	struct sockaddr_in saddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("192.168.1.105");
	ret = bind(listenfd,(struct sockaddr *)&saddr,sizeof(saddr));
	if(ret < 0)
	{
		perror("bind failure!\n");
		return -2;
	}
	printf("bind success!\n");
	//listen
	listen(listenfd,5);

	return listenfd;
}

void myfun(int sig)
{
	wait(NULL);
}

int main()
{
	int pid;
	int ret;
	fd_set rdfs,rdfs_1;
	int maxfd;
	int listenfd, sockfd;
	int len;
	struct sockaddr_in saddr,caddr;
	//signal
	signal(17,myfun);
	//accept
	listenfd = create_server_listenfd();
	len  = sizeof(struct sockaddr_in);
	while(1)
	{
		//init select
		maxfd = listenfd;
		FD_ZERO(&rdfs);
		rdfs_1 = rdfs;
		FD_SET(listenfd,&rdfs_1);
		ret = select(maxfd+1,&rdfs_1,NULL,NULL,NULL);
		if(ret < 0)
		{
			perror("select error!\n");
			return -1;
		}
		printf("select success!\n");
		if(FD_ISSET(listenfd,&rdfs_1))
		{
			sockfd = accept(listenfd,(struct sockaddr *)&caddr,&len);
			if(sockfd < 0)
			{
				perror("accept failure!\n");
				return -1;
			}
			printf("sockfd = %d\n",sockfd);
			printf("IP: 0x%x,Port: %d\n", ntohl(caddr.sin_addr.s_addr), ntohs(caddr.sin_port));
			FD_CLR(listenfd,&rdfs_1);
			maxfd = maxfd > sockfd ? maxfd+1 :sockfd+1;
			FD_SET(maxfd,&rdfs);
		}
		else
		{
			//fork
			pid = fork();
			if(pid == 0)
			{
				int size;
				char read_buf[100] = {0};
				while(1)
				{
					size = recv(sockfd,read_buf,100,0);
					if(size < 0)
					{
						perror("recv failure!\n");
						return -1;
					}
					if(size == 0||(strcmp(read_buf,"quit")==0))
					{
						printf("client connect closed!\n");
						break;
					}
					printf("size: %d\n",strlen(read_buf));
					printf("read_buf: %s\n", read_buf);
					send(sockfd,read_buf,size,0);
					memset(read_buf,0,100);
				}
				close(listenfd);
				close(sockfd);
				exit(0);
			}
			else
			{
				close(sockfd);
			}
		}
	}
	close(listenfd);
	return 0;
}
