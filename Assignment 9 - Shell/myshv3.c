#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAXLINE 1024
#define IC 6

char* internal_commands[]={"cd","history","pwd","clear","exit","ps"};

FILE *fp;

void initialize_shell()
{
	char cwd[MAXLINE]; 
     
	char* username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	
	printf(ANSI_COLOR_BLUE);	
	printf("%s@ubuntu:~", username);	

    printf(ANSI_COLOR_YELLOW);
    printf("%s",cwd);

    printf(ANSI_COLOR_RESET);
    printf("$ ");
}

int sys_call(char** argv, int cd)
{	
	char ch;
	int exf=0;

	if(cd==1 && strcmp(argv[0],"cd")==0)
	{
		if(chdir(argv[1])==-1)
		{
			printf("mysh: cd: %s: No such file or directory\n",argv[1]);
			exf=-1;
		}
	}

	else if(cd==2)
	{
		fp = fopen("history.txt","r");
        ch = fgetc(fp);
       	while(ch != EOF)
        {
            printf("%c",ch);
            ch = fgetc(fp);
        }
	}
	
	else
		exf=system(argv[0]);

	return exf;
}

int execute(char** argv)
{
	int status;

	if(fork()==0)
	{
		if(execvp(argv[0],argv)==-1)
		{
			printf("%s: command not found\n",argv[0]);
			exit(1);
		}
	}

	wait(&status);

	return status;
}

void split(char *line, char **argv)
{
     if(*line == '\0')
     {
         argv[0] = "\0";
         return;
     }

     while (*line != '\0')
     {
          while (*line == ' ' || *line == '\t')
               *line++ = '\0';

          *argv++ = line;

          while(*line != '\0' && *line != ' ' && *line != '\t')
               line++;
     }

    *argv = '\0';
}

int check(char* cmd)
{
	if(strcmp(cmd,internal_commands[1])==0)
		return 2;

	if(strcmp(cmd,internal_commands[0])==0)
		return 1;

	for(int i=3;i<IC;i++)
		if(strcmp(cmd,internal_commands[i])==0)
			return 0;

	if(strcmp(cmd,";")==0 || strcmp(cmd,"||")==0 || strcmp(cmd,"&&")==0 || strcmp(cmd,"|")==0)	//for any special symbol
		return -2;
	
	return -1;	//-1 signifies external command
}

void pip(char** argv, int index)
{
	int pfd[2],i;
	char* argv2[MAXLINE];
	char* argv3[MAXLINE];

	for(i=0;i<index;i++)
		argv2[i]=argv[i];

	argv2[i]='\0';

	for(i=index+1;argv[i]!=0;i++)
		argv3[i-index-1]=argv[i];

	argv3[i-index-1]='\0';

	if(pipe(pfd)<0)
		exit(0);

	if(fork()>0)
	{
		wait(NULL);
		close(pfd[1]);
		dup2(pfd[0],0);
		close(pfd[0]);
		// char *args[]={"./wc2",argv[1],NULL}; 
        execvp(argv3[0],argv3);
	}

	else
	{
		//wait(NULL);
		close(pfd[0]);
		dup2(pfd[1],1);
		close(pfd[1]);
		// char *args[]={"./write",NULL}; 
        execvp(argv2[0],argv2);
		//execlp("ls","ls",(char*)0);
	}
}

int main()
{
	system("clear");
	
	char cmd[MAXLINE];
	char* argv[MAXLINE];
	char* tbe[MAXLINE];
	char* dd;

	int l;

	memset(cmd,0,sizeof(cmd));
	memset(argv,0,sizeof(argv));

	int ef,count,cp,st,tbi,pi;

	fp = fopen("history.txt","w");
    fclose(fp);	

    while(1)
    {
    	count=0;	cp=0;	st=0;	pi=0;

    	initialize_shell();

    	gets(cmd);

    	if(strcmp(cmd,"exit")==0)
    		exit(0);

    	split(cmd,argv);

    	for(int i=0;argv[i]!=0;i++)
    	{
    		count++;

    		if(strcmp(argv[i],"|")==0)
    			pi=i;
    	}

    	// Check for pipe
    	if(pi)
    	{
    		if(fork()==0)
    			pip(argv,pi);
    		
    		wait(NULL);
    		continue;
    	}
  
    	while(cp<count)
    	{
    		tbi=0;
    		memset(tbe,0,sizeof(tbe));
    		while(cp<count)
    		{
    			ef=check(argv[cp]);
				cp++;

    			if(ef==-2)
    				break;

    			tbe[tbi]=argv[cp-1];
    			tbi++;
    		}

    		dd=argv[cp-1];

    		if(ef!=-2)
    			dd="end";

    		ef=check(tbe[0]);

    		if(ef>=0)
    			st=sys_call(tbe,ef);

    		else
    			st=execute(tbe);

    		if(strcmp(dd,"&&")==0 && st!=0)
    			break;

    		if(strcmp(dd,"||")==0 && st==0)
    			break;
    	}
    }
}