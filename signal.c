#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
signal函数能够将子程序交由系统处理，不需要主进程进行等待。
 */

void timeout(int sig)
{
    if(SIGALRM == sig)
        puts("Time out!");
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig == SIGINT)
        puts("CTRL+C pressed.");
}

void terminal(int sig)
{
    if(sig == SIGCHLD)
        puts("child process terminal.");
}

int main(int argc, char const *argv[])
{
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    signal(SIGCHLD, terminal);
    alarm(2);

    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        puts("child process.");
        exit(7);
        // sleep(100);
    }else
    {
        for (i = 0; i < 3; i++)
        {
            puts("wait....");
            sleep(100);
        }
    }
    
    
    return 0;
}
