#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd;
	fd=open("test.txt",O_RDWR | O_APPEND);

	//setuid();

	write(fd,"Program to check permissions\n",strlen("Program to check permissions\n"));
	//printf("Hello! Terminating before closing the file descriptor....\n");
	close(fd);
}
