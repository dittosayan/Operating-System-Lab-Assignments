#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    // make two process which run same program after this instruction
    // program forks and finds factorials
    // numbers entered through command line
    int n=argc-1,index=0,flag=1,fact,num;
    int nums[n];
    // int i,j;
    for(int i=0;i<n;i++)
    	nums[i]=atoi(argv[i+1]);

    pid_t pid;
    pid=fork();

    while(flag!=0) {
    	if(pid>0)
    		flag=0;
      else if(pid==0) {
    		fact=1;
    		num=nums[index];

    		for(int j=1;j<=num;j++)
    			fact*=j;

    		printf("%d\n",fact);
    		index++;

    		if(index<n)
    			pid=fork();
        else {
    			flag=0;
    			exit(0);
    		}
    	}
    }
}
