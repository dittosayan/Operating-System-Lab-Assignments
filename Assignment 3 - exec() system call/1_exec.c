#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int n=argc-1;	//No. of arguments

	char* args[n+1];	//Length of the exec array

	
	//Filling up the exec array with the arguments
	for(int i=0;i<=n;i++)
	{
		if(i==n)
			args[i]=NULL;

		args[i]=argv[i+1];
		//strcat(args[i],"./");
		// printf("%s",args[i]);
	}



	//char *args[]={argv[1],NULL}; 
    //execvp(args[1],args);
	//execvp(argv[2],argv);

	int i,f,t;
    pid_t pid;
    
    for(i=0;i<n;i++)
    {
        pid=fork();

        if(pid == 0)
        {
        	printf("Currently in the driver program, new process created : %d has PID : %d\n",i+1,getpid());
            execvp(args[i],args);
            printf("ERROR! Exec call failed\n");
            exit(0);
        }

        else
        	wait(NULL);
    }

	return 0;
}