#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int factorial(int n)
{
    int fac=1;
    int i;

    for(i=1;i<=n;i++)
      fac*=i;

    return fac;
}

int main(int argc,char *argv[])
{
    int n=argc-1,f;
    pid_t pid;

    // n=argc-1;

    for(int i=0;i<n;i++)
    {
        pid=fork();
        if(pid == 0) {
            f=factorial(atoi(argv[i+1]));
            printf("Factorial of %s is %d\n",argv[i+1],f);
            exit(0);
        }
    }
}
