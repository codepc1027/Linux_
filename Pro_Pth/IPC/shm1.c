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

int main()
{
	int shmid;
	shmid = shmget(IPC_PRIVATE,128,IPC_CREAT|0777);
	if(shmid<0)
	{
		perror("IPC crate fauilt!\n");
		return -1;
	}
	printf("create IPC success!\n");
	system("ipcs -m");
	return 0;
}
