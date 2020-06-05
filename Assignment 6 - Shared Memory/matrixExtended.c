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
#include <math.h>

int funct(double *b,int m,int n,double d)
{
	for(int i=0;i<m*n;i++)
	{
		for(int j=i+1;j<m*n;j++)
		{
			if((*(b+0+j)-*(b+0+i))<=d && (*(b+0+j)-*(b+0+i))>=0)
				return 0;

			else if((*(b+0+i)-*(b+0+j))<=d && (*(b+0+i)-*(b+0+j))>=0)
				return 0;
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	int shmid,m,n,flag;
	double d;

	m=atoi(argv[1]);
	n=atoi(argv[2]);

	d=atof(argv[3]);

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

	flag=1;
	while(flag)
	{
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

		flag=funct(num->b,m,n,d);


		if(flag==1)
		{
			for (int i = 0; i < m; i++)
    		{
				for (int j = 0; j < n; j++)
        			arr[i][j]=num->b[i][j];
    		}
		}

	}

	printf("Final output is : \n");
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
