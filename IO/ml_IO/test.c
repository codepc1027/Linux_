/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：test.c
*   创 建 者：liujing
*   创建日期：2020年06月10日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
	DIR *dp;
	struct dirent *dir;
	char addr[128] = {0};
	printf("please input wanted to open addr:");
	scanf("%s", addr);

	dp = opendir(addr);
	if(dp==NULL)
	{
		perror("open addr failure!\n");
		return -1;
	}
	printf("open %s success\n", addr);
	while(1)
	{
	dir = readdir(dp);
	if(dir==NULL)
	{
		break;
	}
	printf("inode:%ld,name:%s\n", dir->d_ino,dir->d_name);
	}

	return 0;
}
