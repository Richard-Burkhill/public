#include <stdio.h>
#include <sys/types.h>
int main()
{
    int n =10;
    pid_t pid = vfork(); //creating the child process
    if (pid == 0)          //if this is a chile process
    {
        printf("Child process started\n");
    }
    else//parent process execution
    {
        printf("Now i am coming back to parent process\n");
    }
    printf("value of n: %d \n",n); //sample printing to check "n" value
    return 0;
}