#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
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

void fact(int n)
{
	long long int fact=1;

	for(int i=1;i<=n;i++)
	{
		fact=fact*i;
	}

	printf("Factorial is : %lld\n",fact);
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
		//delay();
		while(*(num+1)!=2)
			{
				if(*(num+3)==1)
					break;
			}
		printf("Number read : ");
		printf("%d\n",*(num+0));
		fact(*(num+0));
		*(num+1)=1;
	}

	shmdt(num);

	// while(getchar()!='q')
	// 	{;}
	shmctl(shmid,IPC_RMID,NULL);
}
