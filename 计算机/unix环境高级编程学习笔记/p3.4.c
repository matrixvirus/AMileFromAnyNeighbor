#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	int val;
	if (argc != 2)
	{
		printf("usage: a.out <descriptor#>");
		exit(0);
	}
	int fd = atoi(argv[1]);
	val = fcntl(fd, F_GETFL, 0);
	if (val < 0)
	{
		printf("fcntl error for id %d\n", fd);
		exit(0);
	}
	switch (val & O_ACCMODE) {
	case O_RDONLY:
		printf("read only,");
		break;
	case O_WRONLY:
		printf("write only,");
		break;
	case O_RDWR:
		printf("read and write,");
		break;
	defaut :
		printf("unknown,");
		break;
	}
	if (val & O_APPEND)
		printf("append,");
	if (val & O_NONBLOCK)
		printf("nonblocking,");
	if (val & O_SYNC)
		printf("synchronous write,");
	printf("\n");
	exit(0);
	return(0);
}
