#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		printf("usage:./main 文件名\n");
		exit(0);
	}
	int a = access(argv[1], R_OK);
	if (a == 0)
	{
		printf("对%s 可读\n", argv[1]);
	}
	else
	{
		printf("对%s 不可读\n", argv[1]);
	}
	exit(0);
}
