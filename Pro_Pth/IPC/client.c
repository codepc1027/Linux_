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

struct shm
{
	int pid;
	char buf[124];
};

void myfun(int sig)
{return ;}

int main()
{
	int pid;
	struct shm *p;
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
	printf("create shm success! shmid=%d\n",shmid);
	p = (struct shm *)shmat(shmid,NULL,0);
	if(p == NULL)
	{
		perror("shmat is failure\n");
		return -2;
	}
	signal(SIGUSR1,myfun);
	//read pid to server
	pid = p->pid;
	//write client pid
	p->pid = getpid();
	kill(pid,SIGUSR2);
//	signal(SIGUSR1,myfun);
	while(1)
	{
		pause();
		printf("client:%s",p->buf);
		kill(pid,SIGUSR2);
	}

	return 0;
}
