#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    // make two process which run same program after this instruction
    int n=argc-1,index=0,num;
    int nums[n];
    // int i,j;
    long int fact;

    for(int i=0;i<n;i++)
    	nums[i]=atoi(argv[i+1]);

    pid_t pid;

    while(index<n && fork()==0) {
      fact=1;
   		num=nums[index++];

  		for(int j=1;j<=num;j++)
   			fact*=j;

   		printf("%ld\n",fact);
    }
}
