/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：pipe_1.c
*   创 建 者：liujing
*   创建日期：2020年06月10日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int fd[2];
	int ret;
	char writebuf[] = "hello!\n";
	char readbuf[128] = {0};
	//create pipe
	ret = pipe(fd);
	if(ret < 0)
	{
		perror("create pipe failure!\n");
		return 0;
	}
	printf("create pipe success!\n");
	//write fd[1]
	write(fd[1],writebuf,sizeof(writebuf));
	//read fd[0]
	read(fd[0],readbuf,sizeof(readbuf));
	printf("readbuf:%s\n", readbuf);
	//read after  pipe -> 0
	//make readbuf -> 0
	memset(readbuf,0,128);
	read(fd[0],readbuf,sizeof(readbuf));
	printf("second readbuf:%s\n", readbuf);

	close(fd[0]);
	close(fd[1]);

	return 0;
}
