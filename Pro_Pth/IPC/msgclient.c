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
#include <sys/msg.h>
#include <sys/ipc.h>
#include <signal.h>
#include <string.h>

struct msgbuf
{
	long mtype;
	char buf[124];
};

int main()
{
	int pid;
	int key;
	int msgid;
	struct msgbuf serbuf,clibuf;
	//create key
	key = ftok("a.c",'a');
	if(key < 0)
	{
		perror("key create failure!\n");
		return -1;
	}
	printf("create key success,key = %d\n", key);
	//create msg
	msgid = msgget(key,IPC_CREAT|0777);
	if(msgid < 0)
	{
		perror("create msg failure!\n");
		return -2;
	}
	printf("create msg success,msgid = %d\n", msgid);
	clibuf.mtype = 200;
	pid = fork();
	if(pid > 0)//client parent process write mtype 200
	{
		while(1)
		{
			memset(clibuf.buf,0,124);
			printf("client parent process write:\n");
			fgets(clibuf.buf,124,stdin);
			msgsnd(msgid,(void *)&clibuf,124,0);
		}
	}
	if(pid == 0)//client child process read mtype 100
	{
		while(1)
		{
			memset(serbuf.buf,0,124);
			printf("client child process read:");
			msgrcv(msgid,(void *)&serbuf,124,100,0);
			printf("%s",serbuf.buf);
		}
	}

	msgctl(msgid,IPC_RMID,NULL);
	system("ipcs -q");

	return 0;
}
