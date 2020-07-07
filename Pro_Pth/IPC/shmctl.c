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
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int main()
{
	int key;
	int shmid;
	char buf[128] = {0};
	char *p;
	key = ftok("./shm1.c",'a');
	if(key < 0)
	{
		perror("create key fauilt!\n");
		return -1;
	}
	printf("create key success!key=%d\n",key);
	shmid = shmget(key,128,IPC_CREAT|0777);
	if(shmid < 0)
	{
		perror("IPC crate fauilt!\n");
		return -2;
	}
	printf("create IPC success!\n");
	system("ipcs -m");
	p = (char *)shmat(shmid,NULL,0);
	if(p==NULL)
	{
		perror("shmat error!\n");
		return -3;
	}
//	fread(p,1,128,stdin);
//	fgets(p,128,stdin);
	scanf("%s",p);
	printf("shm data:%s\n", p);
	shmdt(p);
//	memcpy(p,"abcd",4);
	shmctl(shmid,IPC_RMID,NULL);
	system("ipcs -m");

	return 0;
}
