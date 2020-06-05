#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <limits.h>

void delay()
{
	for(int i=0;i<INT_MAX/4;i++)
	{	
		;
		// for(int j=0;j<10;j++)
		// 	{;}
	}
}

int main(int argc, char* argv[])
{
	key_t key;
	key=1234;

	int shmid=shmget(key,sizeof(int)*3,IPC_CREAT | 0666);
	int* num=(int*)shmat(shmid,NULL,0);
	printf("SHMID : %d\n",shmid);
	
	*(num+3)=0;//termination variable
	*(num+1)=1;//turn variable
	for(int i=1;i<=20;i++)
	{
		*(num+0)=i;
		printf("Number entered : %d\n",*(num+0));
		*(num+1)=2;
		while(*(num+1)!=1)
			{;}
	}
		//delay();
	//}
	*(num+3)=1;
	shmdt(num);
	
}	