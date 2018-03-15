#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
void set_fl(int fd, int flags)
{
	int val = fcntl(fd, F_GETFL, 0);
	if (val < 0)
	{
		printf("fcntl F_GETFL error\n");
		exit(0);
	}
	// 设置某个位
	val |=flags;
	if (fcntl(fd,F_SETFL, val) < 0)
	{
		printf("fcntl F_SETFL error\n");
		exit(0);
	}	
}
void clr_fl(int fd, int flags)
{
	int val = fcntl(fd, F_GETFL, 0);
	if (val < 0)
	{
		printf("fcntl F_GETFL error\n");
		exit(0);
	}
	// 取消某个位
	val &= ~flags;
	if (fcntl(fd, F_SETFL, val) < 0)
	{
		printf("fcntl F_SETFL error\n");
		exit(0);
	}
}
int main(int argc, char ** argv)
{
	clr_fl(0, O_APPEND);
	exit(0);
}
