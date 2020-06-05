#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//Attempting to read from both processes at once
int main() {
	int fd1,fd2,s;

	fd1=open("foo.txt", O_WRONLY | O_CREAT);

	pid_t pid;

	pid=fork();

	char *c = (char *) calloc(100, sizeof(char));
	if(pid==0) {
		printf("\n\nfrom the child process%d!\n\n",getpid());
		s = read(fd1, c, 10);
		printf("File descriptor : %d, No. of bytes read : %d\n", fd1, s);
		c[s] = '\0';
		printf("Those bytes are as follows: %s\n", c);
	}

  else if(pid>0) {
		printf("\n\nfrom the parent process%d!\n\n",getpid());

		s = read(fd1, c, 10);
		printf("File descriptor : %d, No. of bytes read : %d\n", fd1, s);
		c[s] = '\0';
		printf("Those bytes are as follows: %s\n", c);
  }
}
