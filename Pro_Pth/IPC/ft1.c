/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：shm1.c
*   创 建 者：liujing
*   创建日期：2020年06月27日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>

void myfun(int sig)
{
	return;
}

int main()
{
	pid_t pid;
	char *p;
	int shmid;
	shmid = shmget(IPC_PRIVATE,128,IPC_CREAT|0777);
	if(shmid < 0)
	{
		perror("IPC crate failure\n");
		return -1;
	}
	printf("create IPC success!\n");
	p = (char *)shmat(shmid,NULL,0);
	if(p == NULL)
	{
		perror("shmat is failure\n");
		return -2;
	}

	pid = fork();
	if(pid > 0)
	{
		signal(SIGUSR2,myfun);
//		printf("pareant:\n");
		while(1)
		{
			printf("parent:");
			fgets(p,128,stdin);
			kill(pid,SIGUSR1);
			pause();
		}
	}
	if(pid == 0)
	{
		signal(SIGUSR1,myfun);
		while(1)
		{
			pause();
			printf("child data is %s",p);
			kill(getppid(),SIGUSR2);
		}
	}

	return 0;
}
