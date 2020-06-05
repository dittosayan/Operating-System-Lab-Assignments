#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

int flag=0;

void handler(int sig)
{
	printf("\nMessage received : ");
	flag=1;

	return;
}

int main(int argc, char const *argv[])
{

	struct packet
	{
		char a[256];
		int f;
	};

	
	char s[256];
	key_t key;
	pid_t server;

	server=atoi(argv[1]);
	key=atoi(argv[2]);

	signal(SIGUSR1,handler);

	int shmid=shmget(key,sizeof(struct packet),IPC_CREAT | 0666);
	struct packet* num=(struct packet*)shmat(shmid,NULL,0);
	printf("SHMID : %d\n",shmid);

	printf("PID is : %d\n",getpid());

	num->f=2;
	while(1)
	{
		//printf(">");
		if(num->f==2 && flag==0)
		{
			printf("\nEnter message : ");
			scanf("%s",&s);
			if(strcmp(s,"q")==0)
				break;

			strcpy(num->a,s);
			kill(server,SIGUSR1);
			num->f=1;
		}

		if(flag==1)
		{
			printf("%s\n",num->a);
			flag=0;
		}
	}

	shmdt(num);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}