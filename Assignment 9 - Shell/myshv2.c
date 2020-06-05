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
#define IC 7

char* internal_commands[]={"cd","ls","history","pwd","clear","exit","ps"};

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
	char lss[10];

	int len=0;

	strcpy(lss, "ls");

	for(int i=0;argv[i]!='\0';i++)
			len++;

	// printf("Length : %d\n",len);

	if(cd==1 && strcmp(argv[0],"cd")==0)
	{
		if(chdir(argv[1])==-1)
			printf("mysh: cd: %s: No such file or directory\n",argv[1]);
	}

	else if(cd==1 && strcmp(argv[0],"ls")==0)
	{
		if(len==2)
		{
			strcat(lss," ");
			strcat(lss, argv[1]);
		}
		// printf("%s\n",lss);
		system(lss);
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
		system(argv[0]);

	// printf("\n");
	return len;
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
	if(strcmp(cmd,internal_commands[2])==0)
		return 2;

	if(strcmp(cmd,internal_commands[0])==0 || strcmp(cmd,internal_commands[1])==0)
		return 1;

	for(int i=3;i<IC;i++)
		if(strcmp(cmd,internal_commands[i])==0)
			return 0;

	if(strcmp(cmd,";")==0)
		return -2;
	
	if(strcmp(cmd,"||")==0)
		return -3;

	if(strcmp(cmd,"|")==0)
		return -4;

	if(strcmp(cmd,"&&")==0)
		return -5;
	
	return -1;
}

int main()
{
	system("clear");
	printf("welcome to mysh\n");
	
	char cmd[MAXLINE];
	char* argv[MAXLINE];
	char* tbexecuted[MAXLINE];

	int l;
	// char* param;

	memset(cmd,0,sizeof(cmd));
	memset(argv,0,sizeof(argv));

	int exec_flag,c,k,st;

	fp = fopen("history.txt","w");
    fclose(fp);

    // system("ping -c 5 127.0.0.1");
	// char cwd;

	// execvp(argv[0],argv);
	
	while(1)
	{
		k=0;
		c=0;

		initialize_shell();	
		// system("cat mysh.c | wc");	
		// Enter the terminal command(s)
		gets(cmd);

		//Open the file to store the history of all previously entered commands
		fp = fopen("history.txt","a");
        fprintf(fp, "%s\n", cmd);
        fclose(fp);

        // if(strlen(cmd)>0)
        //     add_history(cmd);

		if(strcmp(cmd,"\0")==0)
			continue;

		else if(strcmp(cmd,"exit")==0)
		{
			printf("exiting mysh\n");
			exit(0);
		}

		//Split the command line into different arguments
		split(cmd,argv);

		//Count no. of tokens
		for(int i=0;argv[i]!='\0';i++)
			c++;
		
		while(k<c)
		{
			exec_flag=check(argv[k]);
			memset(tbexecuted,0,sizeof(tbexecuted));

			if(exec_flag==-3 && st==0)	// || in which one statement has executed
				break;

			else if(exec_flag==-3 && st>0) // || in which previous statement has not executed
				k++;

			else if(exec_flag==-4)	//edit later for pipe
			{

			}

			else if(exec_flag==-5 && st==0)	// for &&
				k++;

			else if(exec_flag==-5 && st>0)
				break;

			else if(exec_flag==-2)	// ;
				k++;

			else if(exec_flag>=0)	// cd or ls or history
			{
				tbexecuted[0]=argv[k];

				if(exec_flag==1)	// for cd
				{
					tbexecuted[1]=argv[k+1];
					l=sys_call(tbexecuted,exec_flag);
				}

				else
				{
					tbexecuted[1]="\0";
					l=sys_call(tbexecuted,exec_flag)-1;
				}

				printf("Length : %d\n",l);

				if(l==2)
					k+=2;

				else if(l==1)
					k+=1;

				st=0;
			}

			else
			{
				tbexecuted[0]=argv[k];
				tbexecuted[1]=argv[k+1];
				st=execute(tbexecuted);
				k+=2;
			}
		}

		// else if(exec_flag)
			// printf("Status : %d\n",st);
	}
}