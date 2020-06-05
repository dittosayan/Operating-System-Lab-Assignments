#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char* buff;
	// char shell[10];

	// // scanf("%s",shell);
	// buff=readline(shell);

	if(chdir("/home/sayan/Desktop")<0)
		printf("error\n");

	printf("%s\n", getcwd(buff, 100)); 
	// printf("Buffer : %s\n",buff);
}