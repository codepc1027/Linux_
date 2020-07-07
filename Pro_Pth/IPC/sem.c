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
#include <sys/sem.h>
#include <sys/ipc.h>

union semun mysemun;
int semid;
struct sembuf mysembuf;

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo * _buf;
};

void myfun(void *arg)
{
	int i;
	mysembuf.sem_op = -1;
	semop(semid,&mysembuf,1);
	for(i = 0;i < 10;i++)
	{
		printf("child pthread is:%d\n", i);
	}
}

int main()
{
	int i;
	pthread_t ptd;
	int ret;
	//create sem
	semid = semget(IPC_PRIVATE,3,0777);
	if(semid < 0)
	{
		perror("create sem failure!\n");
		return -1;
	}
	printf("sem create success!semid = %d\n", semid);
	system("ipcs -s");
	//init sem
	mysemun.val = 0;
	semctl(semid,0,SETVAL,mysemun);

	mysembuf.sem_num = 0;
	mysembuf.sem_flg = 0;

	//create pthread
	ret = pthread_create(&ptd,NULL,myfun,NULL);
	if(ret < 0)
	{
		perror("pthread create failure!\n");
		return -2;
	}
	printf("pthread create success!\n");

	for(i = 0;i < 10;i++)
	{
		printf("parent pthread is:%d\n", i);
	}
	mysembuf.sem_op = 1;
	semop(semid,&mysembuf,1);

	while(1);
	return 0;
}
