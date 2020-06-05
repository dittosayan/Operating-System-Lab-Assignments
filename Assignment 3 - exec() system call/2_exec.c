#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int n=argc-1;	//No. of arguments

	char* args[n+1];
	char* s1="./";

	//Filling up the exec array with the arguments
	for(int i=0;i<=n;i++)
	{
		 // +1 for the null-terminator
    // in real code you would check for errors in malloc here

		if(i==n)
			args[i]=NULL;

		args[i]=argv[i+1];

		char *result = malloc(strlen(s1) + strlen(args[i]) + 1);
		memcpy(result,s1,strlen(s1));
		memcpy(result+strlen(s1),args[i],strlen(args[i]));
    args[i]=result;
    free(result);
	}

	int i,f;
  pid_t pid;

  for(i=0;i<n;i++)
	{
        pid=fork();

        if(pid == 0)
        {
        	printf("%d\n",getpid());
            execvp(args[i],args);
            exit(0);
        }
    }

	return 0;
}
