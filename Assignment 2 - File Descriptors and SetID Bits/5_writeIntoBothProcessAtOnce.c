#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

//Writing into the parent and child process at once

int main() {

	int fd1,fd2,s;
	fd2=open("foo2.txt", O_WRONLY | O_CREAT);
	pid_t pid;

	pid=fork();

	char *c = (char *) calloc(100, sizeof(char));
	if(pid==0) {
		printf("\n\nHello from the child process!!!!!!!!!!!\n\n");
		// s = read(fd1, c, 10);
  	// printf("File descriptor : %d, No. of bytes read : %d\n", fd1, s);
  	// c[s] = '\0';
  	// printf("Those bytes are as follows: %s\n", c);
    write(fd2,"Hello world child process\n",strlen("Hello world child process\n"));
  }

  else if(pid>0) {
		printf("\n\nHello from the parent process!!!!!!!!!!!\n\n");
    // s = read(fd1, c, 10);
    // printf("File descriptor : %d, No. of bytes read : %d\n", fd1, s);
    // c[s] = '\0';
    // printf("Those bytes are as follows: %s\n", c);
    write(fd2,"Hello world child process\n",strlen("Hello world child process\n"));
  }
}
