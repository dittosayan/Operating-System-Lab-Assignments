#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

#define MUTEX 0
#define WRT 1

union semun{
	int val;
	struct semid_ds *buf;
	ushort array;
}arg;

void setsem(int semid,int semnum)
{
	arg.val=1;
	if(semctl(semid,semnum,SETVAL,arg)<0)
		printf("Error in setsem");

	// if(semctl(semid,semnum,GETVAL,arg)<0)
	// 	printf("Error in value getting value\n");
	
	// printf("Semaphore value : %d\n",arg.val);
}

void wait(int semid,int semnum)
{
	struct sembuf b;

	b.sem_num=semnum;
	b.sem_op=-1;
	b.sem_flg=0;

	if(semop(semid,&b,1)<0)
		printf("Error in semop from wait\n");
}

void signl(int semid,int semnum)
{
	struct sembuf b;

	b.sem_num=semnum;
	b.sem_op=+1;
	b.sem_flg=0;

	if(semop(semid,&b,1)<0)
		printf("Error in semop from signl\n");
}

int main(int argc, char const *argv[])
{
	int semid,wfd;
	key_t key=1234;
	key_t key_s=5678;
	
	char c;
	char* buf;
	//Open the file to write
	wfd=open("read.txt",O_CREAT | O_WRONLY | O_APPEND);

	semid=semget(key,2,IPC_CREAT | 0666);
	printf("Semid : %d\n",semid);

	//Initialize the values for the wrt semaphore
	// if(atoi(argv[1])==0)
	// 	setsem(semid,WRT);

	//Wait for the wrt semaphore
	wait(semid,WRT);

	//Enter critical section
	printf("Entered the critical section\n");
	printf("Enter input : ");
	scanf("%s",buf);
	buf[strlen(buf)]='\n';
	write(wfd,buf,strlen(buf));
	
	printf("Write Complete");
	gets(&c);
	close(wfd);

	gets(&c);

	//Signal the wrt semaphore
	signl(semid,WRT);
	printf("Exited from critical section\n");
	return 0;
}