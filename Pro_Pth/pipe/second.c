/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：first.c
*   创 建 者：liujing
*   创建日期：2020年06月11日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
//	char buf[128] = {0};
//      int flag = 1;
        int flag = 1;
	int i;
	int fd;
	fd = open("mkfifo",O_RDONLY);
	if(fd < 0)
	{
		perror("open mkfifo failure!\n");
		return -1;
	}
//	read(fd,&flag,1);
	for(i=0; i<5; i++)
	{
		printf("second process :%d\n", i);
	}
//	read(fd,buf,128);
//	printf("second buf:%s\n", buf);
	read(fd,&flag,1);
	printf("flag=%d\n",flag);

	return 0;
}
