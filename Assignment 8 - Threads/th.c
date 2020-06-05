#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h>
#include <sys/types.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <netdb.h>

int buffer=0;	//Initialize the buffer variable
pthread_mutex_t bufLock;
int count[3];

void increment(int index)
{
	while(1)
	{

		pthread_mutex_lock(&bufLock);
		
		if(buffer==24)
			pthread_exit();

		buffer++;
		count[index]+=1;

		printf("TID : %x\nBuffer value : %d\n\n",pthread_self(),buffer);
		
		pthread_mutex_unlock(&bufLock);
		sleep(0.5);
	}

	pthread_exit();
}

int main(int argc, char const *argv[])
{
	pthread_t tid1,tid2,tid3;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_mutex_init(&bufLock);

	pthread_create(&tid1,&attr,&increment,0);
	
	pthread_create(&tid2,&attr,&increment,1);
	
	pthread_create(&tid3,&attr,&increment,2);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	printf("Count of no. of operations by each thread is\n");
	// for(int i=0;i<3;i++)
	// 	printf("Thread %d : %d\n",i+1,count[i]);

	printf("Thread %x : %d\n",tid1,count[0]);
	printf("Thread %x : %d\n",tid2,count[1]);
	printf("Thread %x : %d\n",tid3,count[2]);

	return 0;
}