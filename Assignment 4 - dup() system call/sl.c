#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char* argv[])
{
	int pfd[2];

	if(pipe(pfd)<0)
		exit(0);

	if(fork()==0)
	{
		wait(NULL);
		close(pfd[1]);
		dup2(pfd[0],0);
		close(pfd[0]);
		char *args[]={"./wc2",argv[1],NULL};
    execvp(args[0],args);
	}

	else
	{
		//wait(NULL);
		close(pfd[0]);
		dup2(pfd[1],1);
		close(pfd[1]);
		char *args[]={"./write",NULL};
    execvp(args[0],args);
		//execlp("ls","ls",(char*)0);
	}
}
