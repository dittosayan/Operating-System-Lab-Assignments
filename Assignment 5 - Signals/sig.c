#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

void handler(int sig) 
{ 
    printf("Caught signal\n");
    //fflush(stdin);

    // printf("Message received is : %s\n",num);
    // memset(num,NULL,sizeof(num)); 
}
  
int main(int argc,char* argv[]) 
{ 
	int i;
	signal(SIGUSR1, handler);

	pid_t pid,client;
	pid=getpid();
	
	printf("Process ID is : %d\n",pid);

	key_t key;	
	key=1234;

	//printf("Key : %d\n",key);

	int shmid=shmget(key,100,IPC_CREAT | 0666);
	char* num=(char*)shmat(shmid,NULL,0);
	printf("SHMID : %d\n",shmid);

	char* a;

	printf("Enter PID of client : ");
	scanf("%d",&client);

	
	while(1)
	{
		printf(">");
		
		scanf("%s",&a);
		
		if(strcmp(&a,"q")==0)
			break;
		
		strcpy(num,&a);
		kill(client,SIGUSR1);
	}
	
	shmdt(num);
	shmctl(shmid,IPC_RMID,NULL);
} 