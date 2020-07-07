/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：fork.c
*   创 建 者：liujing
*   创建日期：2020年06月10日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		int i;
  		for(i=0; i<6; i++)
		{
			printf("child process is: %d\n", i);
			usleep(100);
		}
	}
	if(pid > 0)
	{
		int i;
		for(i=0; i<6; i++)
		{
			printf("parent process is : %d\n", i);
			usleep(100);
		}
	}
	
	return 0;
}
