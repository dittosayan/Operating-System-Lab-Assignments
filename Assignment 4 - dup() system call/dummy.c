#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int fd;

	fd=open("text.txt",O_CREAT | O_RDWR);
	write(fd,"Sample text\0",strlen("Sample text\0"));
	close(fd);
}