#include <unistd.h>
#include <stdio.h>


int gval = 10;
int main()
{
    pid_t pid;
    int lval = 20;
    gval++, lval += 5;

    pid = fork();
    if (pid == 0)   //child process
    {
        gval += 2;
        lval += 2;
    }else
    {
        gval -= 2;
        lval -= 2;
    }

    if (0 == pid)
        printf("Child proc: [%d, %d]\n", gval, lval);
    else
        printf("Parent proc: [%d, %d]\n", gval, lval);
        
    return 0;
}