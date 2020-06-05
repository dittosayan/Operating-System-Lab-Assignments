#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int i=0,j;
	char* a[20];
	char temp;
	//scanf("%s",&a);
	system("/bin/stty raw");
	temp=getchar();

	while(1)
	{
		a[i]=temp;
		i++;

		if(temp==EOF)
		{
			a[i]='\0';
			break;
		}

		else if(temp=='\x0A')
			a[i]='\n';

		temp=getchar();
	}
	system("/bin/stty cooked");
	
	for(j=0;j<i;j++)
		printf("%c",a[j]);
}