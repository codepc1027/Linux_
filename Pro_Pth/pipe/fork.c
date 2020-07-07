/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：fork.c
*   创 建 者：liujing
*   创建日期：2020年06月10日
*   描    述：
*   利用读阻塞实现父进程先运行
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	char flag = 0;
	int fd[2];
	int ret = 0;
	ret = pipe(fd);
	if(ret < 0)
	{
		perror("create pipe failure!\n");
		return -1;
	}
	printf("create pipe success!\n");

	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		read(fd[0],&flag,1);
		int i;
  		for(i=0; i<6; i++)
		{
			printf("child process is: %d\n", i);
		}
	}
	if(pid > 0)
	{
		int i;
		for(i=0; i<6; i++)
		{
			printf("parent process is : %d\n", i);
		}	
                write(fd[1],&flag,1);
	}
	
	return 0;
}
