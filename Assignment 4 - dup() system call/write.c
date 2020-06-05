#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int i=0,j,sp,ln;
	char* a[20];
	//scanf("%s",&a);
	//system("/bin/stty raw");
	a[i]=getchar();
	while(a[i]!=EOF)
	{
		i++;
		a[i]=getchar();
	}
	//system("/bin/stty cooked");

	sp=0;
	ln=0;
	for(j=0;j<i;j++)
	{
		if(a[j]==' ')
			sp++;

		if(a[j]=='\n')
			ln++;
		printf("%c",a[j]);
	}

	//printf("Spaces : %d\nLines : %d\n",sp,ln);
}
