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

int mz_ipv4_tcp_create_socket(void)
{
	int listenfd, sockfd, opt = 1;
	struct sockaddr_in server, client;
	socklen_t len;
	int timep;
	int ret;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0){
		perror("Create socket fail.");
		return -1;
	}

	if ((ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0){
		perror("Error, set socket reuse addr failed");
		return -1;
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = inet_addr("192.168.1.105");

	len = sizeof(struct sockaddr);
	if (bind(listenfd, (struct sockaddr *)&server, len)<0){
		perror("bind error.");
		return -1;
	}

	listen(listenfd, 1024);

	return listenfd;
}

int main()
{
	int listenfd, sockfd;
	struct sockaddr_in server, client;
	socklen_t len;
	int bytes = 0;
	fd_set global_rdfs, current_rdfs;
	int maxfd;
	int i;
	char buf[1024];

	len = sizeof(struct sockaddr_in);

	listenfd = mz_ipv4_tcp_create_socket();
	FD_ZERO(&global_rdfs);
	FD_SET(listenfd, &global_rdfs);
	maxfd = listenfd;

	while (1){
		current_rdfs = global_rdfs;
		if (select(maxfd + 1, &current_rdfs, NULL, NULL, NULL)<0){
			perror("select error.\n");
			return -1;
		}

		for (i = 0; i <= maxfd; i++){

			if (FD_ISSET(i, &current_rdfs)){
				if (listenfd == i){
					if ((sockfd = accept(listenfd, (struct sockaddr *)&client, &len))<0){
						perror("accept error.\n");
						return -1;
					}
					printf("sockfd:%d\n", sockfd);
					FD_CLR(i,&current_rdfs);
					maxfd = maxfd > sockfd ? maxfd+1 : sockfd+1;
					FD_SET(sockfd, &global_rdfs);
				}
				else{
					printf("read socket:%d\n", i);
					bytes = recv(i, buf, 1024, 0);
					if (bytes < 0){
						perror("recv error.\n");
						return -1;
					}
					if (bytes == 0){
						FD_CLR(i, &global_rdfs);
						close(i);
						continue;
					}
					printf("buf:%s\n", buf);
					send(i, buf, strlen(buf), 0);
				}

			}

		}
	}
}
