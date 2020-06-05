#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int shmid,m,n;

	m=atoi(argv[1]);
	n=atoi(argv[2]);

  int *a=(int*)malloc(m*n*sizeof(int));
  double sum,ck;

  struct Matrix
  {
  	double b[m][n];
  };

  int *arr[m];

  for (int i=0; i<m; i++)
       arr[i] = (int *)malloc(n * sizeof(int));

	printf("Enter input array\n");
  for (int i = 0; i <  m; i++)
  {
  	for (int j = 0; j < n; j++)
    	{
    		scanf("%d",&arr[i][j]);
    	}
	}

	printf("Array inputed is\n");
  for (int i = 0; i < m; i++)
  {
	for (int j = 0; j < n; j++)
      	printf("%d ", arr[i][j]);

   	printf("\n");
  }


	shmid=shmget(IPC_PRIVATE,sizeof(struct Matrix),IPC_CREAT | 0666);
	struct Matrix *num=(struct Matrix*)shmat(shmid,NULL,0);

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			ck=0.0;
			sum=0.0;
			if(fork()==0)
			{
				if((i-1)>=0 && (j-1)>=0)
				{
					sum+=arr[i-1][j-1];
					ck=ck+1;
				}

				if((i-1)>=0 && (j)>=0)
				{
					sum+=arr[i-1][j];
					ck=ck+1;
				}

				if((i-1)>=0 && (j+1)<n)
				{
					sum+=arr[i-1][j+1];
					ck=ck+1;
				}

				if((i)>=0 && (j-1)>=0)
				{
					sum+=arr[i][j-1];
					ck=ck+1;
				}

				if((i)>=0 && (j)>=0)
				{
					sum+=arr[i][j];
					ck=ck+1;
				}

				if((i)>=0 && (j+1)<n)
				{
					sum+=arr[i][j+1];
					ck=ck+1;
				}

				if((i+1)<m && (j-1)>=0)
				{
					sum+=arr[i+1][j-1];
					ck=ck+1;
				}

				if((i+1)<m && (j)>=0)
				{
					sum+=arr[i+1][j];
					ck=ck+1;
				}

				if((i+1)<m && (j+1)<n)
				{
					sum+=arr[i+1][j+1];
					ck=ck+1;
				}
				num->b[i][j]=sum/ck;
				exit(0);
			}

			else
				wait(NULL);
		}
	}

	printf("Output is : \n");
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++)
			printf("%f ",num->b[i][j]);

		printf("\n");
	}
	shmdt(num);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
