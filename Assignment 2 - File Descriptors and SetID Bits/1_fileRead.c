#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
	int fd1,fd2,s;
	fd1=open("foo.txt", O_RDONLY | O_CREAT);

	char *c = (char *) calloc(100, sizeof(char));
	s = read(fd1, c, 10);
	printf("called read(% d, c, 10).  returned that"
       " %d bytes  were read.\n", fd1, s);
	c[s] = '\0';
	printf("Those bytes are as follows: %s\n", c);
}
