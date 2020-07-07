/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：mkfifo.c
*   创 建 者：liujing
*   创建日期：2020年06月11日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
	int ret;
	ret = mkfifo("mkfifo",0777);
	if(ret < 0)
	{
		perror("create mkfifo failure!\n");
		return -1;
	}
	printf("create mkfifo success!\n");

	return 0;
}
