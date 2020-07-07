/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：client.c
*   创 建 者：liujing
*   创建日期：2020年05月19日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int ret = 0;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("192.168.1.105");
	ret = connect(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
	if(ret < 0)
	{
		perror("connet faillure!\n");
		return -1;
	}

	printf("客户端已连入服务器\n");
	char read_buf[100] = {0};
	char buf[100] = {0};
	while(1)
	{
		printf("please inout:");
		scanf("%s",buf);
		ret = send(sockfd, buf, strlen(buf),0);
		if(ret < 0)
		{
			perror("write failure!\n");
			return -1;
		}
		ret = recv(sockfd,read_buf,sizeof(read_buf),0);
		if(ret < 0)
		{
			perror("read failure!\n");
			return -1;
		}
		printf("read_buf: %s\n",read_buf);
		memset(read_buf,0,100);
		if(strcmp(buf, "quit") == 0)
			return;
	}
	close(sockfd);
	return 0;
}
