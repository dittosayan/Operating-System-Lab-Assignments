#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fd,s,sp=0,ln=1,charac=0;
	char ch;
	fd=open("text.txt",O_RDONLY | O_CREAT);

	// s=read(fd,&ch,1);
	// printf("%c",ch);
	// s=read(fd,&ch,1);
	// printf("%c",ch);
	while(1) {
		s=read(fd,&ch,1);
		// printf("%c",ch);
		if(ch=='\x04')
			break;

		else if(ch==' ')
			sp++;

		else if(ch=='\n')
			ln++;

		printf("%c",ch);
		charac++;
	}

	if(strcmp(argv[1],"-c")==0)
		printf("\nNo. of charachters : %d\n",charac);

	else if(strcmp(argv[1],"-l")==0)
		printf("\nNo. of lines : %d\n",ln);

	else if(strcmp(argv[1],"-w")==0)
		printf("\nNo. of words : %d\n",sp+ln);

	else
		printf("\nSpaces : %d\nLines : %d\nWords : %d\n",sp,ln,sp+ln);
}
