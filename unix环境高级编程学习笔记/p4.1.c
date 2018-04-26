#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		printf("usage:./main 文件名\n");
		exit(0);
	}
	struct stat buf;
	char * ptr;
	if (lstat(argv[1],&buf) < 0)
	{
		perror(NULL);
		exit(0);
	}
	if (S_ISREG(buf.st_mode))
		ptr = "regular";
	else if (S_ISDIR(buf.st_mode))
		ptr = "directory";
	else if (S_ISCHR(buf.st_mode))
		ptr = "character special";
	else if (S_ISBLK(buf.st_mode))
		ptr = "block special";
	else if (S_ISFIFO(buf.st_mode))
		ptr = "fifo";
	else if (S_ISLNK(buf.st_mode))
		ptr = "symbolic link";
	else if (S_ISSOCK(buf.st_mode))
		ptr = "socket";
	else
		ptr = "unknown";
	printf("%s %s\n", argv[1], ptr);
	exit(0);
}


