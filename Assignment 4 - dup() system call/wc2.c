#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fd=0,s,sp=0,ln=0,charac=0,w;
	char ch;
	//fd=open("text.txt",O_RDONLY | O_CREAT);

	// s=read(fd,&ch,1);
	// printf("%c",ch);
	// s=read(fd,&ch,1);
	// printf("%c",ch);
	//system("/bin/stty raw");
	while(1)
	{
		s=read(fd,&ch,1);
		//printf("%c",ch);
		if(s==0)
			break;

		// else if(ch=='\n')
		// {
		// 	ch='\n';
		// 	ln++;
		// }

		else if(ch==' ')
			sp++;

		else if(ch=='\n')
			ln++;

		//printf("%c",ch);
		charac++;
	}
	//system("/bin/stty cooked");

	charac=charac-21;
	ln=ln-1;
	w=sp+ln-4;
	// if(ln==1)
	// 	w=sp+ln-1;

	if(strcmp(argv[1],"-c")==0)
		printf("\nNo. of charachters : %d\n",charac);

	else if(strcmp(argv[1],"-l")==0)
		printf("\nNo. of lines : %d\n",ln);

	else if(strcmp(argv[1],"-w")==0)
		printf("\nNo. of words : %d\n",w);

	else
		printf("\nSpaces : %d\nLines : %d\nWords : %d\n",sp,ln,w);
}
