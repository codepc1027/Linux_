/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：pthread_test.c
*   创 建 者：liujing
*   创建日期：2020年06月10日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <pthread.h>
int flag = 0;

void *fun(void * arg)
{
	int i;
	while(flag==0);
	for(i=0; i<6; i++)
	{
		printf("pthread is: %s\n", arg);
	}
}

int main()
{
	int ret = 0;
	int i;
	char str[] = "hello\n";

	pthread_t pid;
	ret = pthread_create(&pid,NULL,fun,(void *)str);
	if(ret < 0)
	{
		perror("pthread create failure!\n");
		return -1;
	}
	for(i=0; i<6; i++)
	{
		printf("main is: %s\n", str);
	}
	flag = 1;

	while(1);
	return 0;
}
