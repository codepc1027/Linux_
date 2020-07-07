/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：server_epoll.c
*   创 建 者：PC
*   创建日期：2020年07月04日
*   描    述：epoll server
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_EVENTS 100
#define EPOLL_SIZE 50

int listenfd_create()
{
	int listenfd;
	int ret;
	int opt = 1;
	struct sockaddr_in saddr;

	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd < 0)
	{
		perror("create sockfd err!\n");
		return -1;
	}
	ret = setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	if(ret < 0)
	{
		perror("addr reuse err!\n");
		return -1;
	}
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("192.168.1.105");
	ret = bind(listenfd,(struct sockaddr *)&saddr,sizeof(saddr));
	if(ret < 0)
	{
		perror("bind err!\n");
		return -1;
	}
	listen(listenfd,5);
	printf("init success\n");

	return listenfd;
}

int main()
{
	int listenfd;
	int sockfd;
	int epollfd;
	int i;
	int ret;
	int size;
	int len;
	char read_buf[100] = {0};
	struct epoll_event ev, events[MAX_EVENTS];
	struct sockaddr_in caddr;

	len = sizeof(struct sockaddr_in);
	listenfd = listenfd_create(5);
	epollfd = epoll_create(EPOLL_SIZE);
	if(epollfd < 0)
	{
		perror("epoll create err!\n");
		return -1;
	}
	ev.data.fd = listenfd;
	ev.events = EPOLLIN;
	ret = epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&ev);
	if(ret < 0)
	{
		perror("epoll_ctl err!\n");
		return -1;
	}

	while(1)
	{
		ret = epoll_wait(epollfd,events,MAX_EVENTS,-1);
		if(ret < 0)
		{
			perror("epoll_wait err!\n");
			return -1;
		}
		for(i = 0; i < MAX_EVENTS; i++)
		{
			if(events[i].data.fd == listenfd)
			{
				sockfd = accept(events[i].data.fd,(struct sockaddr *)&caddr,&len);
				if(sockfd < 0)
				{
					perror("accept err!\n");
					return -1;
				}
				printf("client,IP: 0x%x,Port: %d\n",ntohl(caddr.sin_addr.s_addr),ntohs(caddr.sin_port));
				printf("sockfd = %d\n", sockfd);
				ev.data.fd = sockfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev);
				continue;
			}
			else
			{
				size = recv(sockfd,read_buf,sizeof(read_buf),0);
				if(size < 0)
				{
					perror("recv err!\n");
					return -1;
				}
				if(size == 0)
				{
					close(sockfd);
					epoll_ctl(epollfd,EPOLL_CTL_DEL,sockfd,&ev);
					continue;
				}
				printf("size: %d\n",size);
				printf("read_buf: %s\n", read_buf);
				send(sockfd,read_buf,size,0);
			 	memset(read_buf,0,100);
			}
		}
	}
	close(listenfd);
	return 0;
}
