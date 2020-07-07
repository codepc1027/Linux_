/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：kill.c
*   创 建 者：liujing
*   创建日期：2020年06月11日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	int ret;
	int sig = atoi(argv[1]);
	int pid = atoi(argv[2]);
	printf("sig = %d,pid = %d\n", sig,pid);	
	ret = kill(pid,sig);
	return 0;
}
