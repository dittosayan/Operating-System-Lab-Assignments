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
  int x,y;
  double sum,ck;

  struct Matrix
  {
  	double b[m][n];
  	int r;
  	int c;
  };

  int *arr[m];

  for (int i=0; i<m; i++)
		arr[i] = (int *)malloc(n * sizeof(int));

	printf("Enter input array\n");
  for (int i = 0; i <  m; i++) {
  	for (int j = 0; j < n; j++)
    		scanf("%d",&arr[i][j]);
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
			num->r=i;
			num->c=j;
			ck=0.0;
			sum=0.0;
			if(fork()==0)
			{
				x=num->r;
				y=num->c;
				if((x-1)>=0 && (y-1)>=0)
				{
					sum+=arr[x-1][y-1];
					ck=ck+1;
				}

				if((x-1)>=0 && (y)>=0)
				{
					sum+=arr[x-1][y];
					ck=ck+1;
				}

				if((x-1)>=0 && (y+1)<n)
				{
					sum+=arr[x-1][y+1];
					ck=ck+1;
				}

				if((x)>=0 && (y-1)>=0)
				{
					sum+=arr[x][y-1];
					ck=ck+1;
				}

				if((x)>=0 && (y)>=0)
				{
					sum+=arr[x][y];
					ck=ck+1;
				}

				if((x)>=0 && (y+1)<n)
				{
					sum+=arr[x][y+1];
					ck=ck+1;
				}

				if((x+1)<m && (y-1)>=0)
				{
					sum+=arr[x+1][y-1];
					ck=ck+1;
				}

				if((x+1)<m && (y)>=0)
				{
					sum+=arr[x+1][y];
					ck=ck+1;
				}

				if((x+1)<m && (y+1)<n)
				{
					sum+=arr[x+1][y+1];
					ck=ck+1;
				}
				//num->b[i][j]=arr[i][j]+1;

				//printf("%d,%d Sum : %f\nCount : %f\n",i,j,sum,ck);
				//sum=(sum)/ck;
				num->b[x][y]=sum/ck;
				//printf("Value Inserted : %f",num->b[x][y]);
				exit(0);
			}

			else
				wait(NULL);
		}
	}

	printf("Output is : \n");
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%f ",num->b[i][j]);
		}
		printf("\n");
	}
	shmdt(num);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
