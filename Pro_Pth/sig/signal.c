/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：kill.c
*   创 建 者：liujing
*   创建日期：2020年06月11日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void myfun(int signal)
{
	int i;
	for(i = 0; i < 5; i++)
	{
		printf("myfun is :%d\n", i);
	}
	return;
}
void myfun1(int signal)
{
	wait(NULL);
}

int main()
{
	int i = 0;
	pid_t pid;
	pid = fork();

	if(pid == 0)
	{
		sleep(5);
		kill(getppid(),14);
		sleep(5);
		exit(0);//signal = 17;
	}
	if(pid > 0)
	{
		signal(17,myfun1);
		signal(14,myfun);
		while(1)
		{
			printf("parent process:%d\n", i);
			sleep(1);
			i++;
		}
	}
	return 0;
}
