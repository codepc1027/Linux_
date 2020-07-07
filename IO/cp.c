/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：cp.c
*   创 建 者：liujing
*   创建日期：2020年06月07日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])//argc参数个数,argv[]参数数组
{
	int rd_fd,wd_fd;
	int rd_ret = 0;
	char rd_buf[128] = {0};

	if(argc < 3)
	{
		perror("please input src file and des file!\n");
		return -1;
	}
	//打开源文件
	rd_fd = open(argv[1],O_RDONLY);
	if(rd_fd < 0)
	{
		printf("open src file %s failure!\n", argv[1]);
		return -2;
	}
	printf("open src file %s success,rd_fd = %d\n", argv[1],rd_fd);
	//打开目标文件
	wd_fd = open(argv[2],O_RDWR|O_CREAT,0777);
	if(wd_fd < 0)
	{
		printf("open des file %s failure!\n", argv[2]);
		return -3;
	}
	printf("open des file %s success,wd_fd = %d\n", argv[2],wd_fd);

	while(1)//循环读取，buf太小
	{
		//从目标文件读数据到缓冲区
		rd_ret = read(rd_fd,rd_buf,sizeof(rd_buf));
		if(rd_ret < 0)
		{
			printf("read src file %s failure!\n", argv[1]);
			return -4;
		}
		//缓冲区里读不满，说明文件要读完了，再读一次退出循环
		if (rd_ret < 128)
		{
			rd_ret = write(wd_fd,rd_buf,rd_ret);
			break;
		}
		//把缓冲区里的数据写给目标文件
		rd_ret = write(wd_fd,rd_buf,rd_ret);
		if(rd_ret < 0)
		{
			printf("write des file %s failure!\n", argv[2]);
			return -5;
		}
	}
	//关闭文件
	close(rd_fd);
	close(wd_fd);

	return 0;
}
