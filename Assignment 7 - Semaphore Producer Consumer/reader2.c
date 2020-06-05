#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/shm.h>

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

	printf("\n");
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
	int semid,rfd,shmid;
	char ch;
	key_t key=1234;
	key_t key_s=5678;

	char* buf;

	//Create the shared memory
	shmid=shmget(key_s,sizeof(int)*2,IPC_CREAT | 0666);
	int *rc=(int*)shmat(shmid,NULL,0);
	
	//Open the file to write
	rfd=open("read.txt",O_CREAT | O_RDONLY);

	semid=semget(key,2,IPC_CREAT | 0666);

	//Initialize the values for the semaphore
	// if(atoi(argv[1])==0)
	// 	*rc=0;

	while(*(rc+1)==1);
	wait(semid,MUTEX);


	*rc=*rc+1;

	if(*rc==1)
		wait(semid,WRT);

	printf("Readcount : %d\n",*rc);

	signl(semid,MUTEX);



	//Enter the critical section
	printf("Critical section of the reader\n");
	
	while(read(rfd, buf, 1)!=0)
		printf("%s",buf);

	printf("\n");

	gets(&ch);
	
	wait(semid,MUTEX);

	*rc=*rc-1;

	signl(semid,MUTEX);
	
	if(*rc==0)
		signl(semid,WRT);
	
	//shmdt(rc);
	//shmctl(shmid,IPC_RMID,NULL);
	return 0;
}	