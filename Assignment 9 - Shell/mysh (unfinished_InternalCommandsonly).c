#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024
#define IC 4

char* internal_commands[]={"pwd","ls","bash","ps"};
char* external_commands[]={"cat","man","echo","ls","mkdir"};

void initialize_shell()
{
	char cwd[MAXLINE]; 
     
	char* username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	
	printf("%s@ubuntu:~", username);	

    printf("%s",cwd);
    printf("$ ");
}

int check(char* cmd)
{
	for(int i=0;i<IC;i++)
	{
		if(strcmp(cmd,internal_commands[i])==0)
			return 0;

		else if(strcmp(cmd,external_commands[i])==0)
			return 1;
	}
}

void sys_call(char* cmd)
{
	printf("\n");
	system(cmd);

	printf("\n");
	return;
}

// void tokenize()
// {

// }

int main()
{
	char cmd[MAXLINE];
	int exec_flag;
	//char cwd;
	
	while(1)
	{
		initialize_shell();
		scanf(" %[^\t\n]s",cmd);
		// tokenize();
		exec_flag=check(cmd);

		if(exec_flag==0)
			sys_call(cmd);

		else if(exec_flag)
			printf("External command\n");
	}
}