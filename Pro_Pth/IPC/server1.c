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
#include <string.h>

int main()
{
	char *p;
	int pid;
	int shmid;
	int key;
	key = ftok("a.c",'a');
	printf("key = %d\n",key);
	shmid = shmget(key,128,IPC_CREAT|0777);
	if(shmid < 0)
	{
		perror("shm crate failure\n");
		return -1;
	}
	printf("create shm success!shmid=%d\n",shmid);
	p = (char *)shmat(shmid,NULL,0);
	if(p == NULL)
	{
		perror("shmat is failure\n");
		return -2;
	}
//	signal(SIGUSR2,myfun);
	while(1)
	{
		printf("server:");
		fgets(p,128,stdin);
	}

	return 0;
}
