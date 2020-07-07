/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：cat.c
*   创 建 者：liujing
*   创建日期：2020年06月08日
*   描    述：
*	fputc,fgetc 完成cat指令
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	FILE *src_fp;
	int rd_ret = 0;
	//打开源文件
	src_fp = fopen(argv[1], "w+");
	if(src_fp == NULL)
	{
		printf("open src file %s failure!\n", argv[1]);
		return -2;
	}
	fputc('a', src_fp);
	fflush(src_fp)
	fseek(src_fp,0,SEEK_SET);
	fgetc(src_fp);
	
	while(1);
	fclose(src_fp);
	return 0;
}
