#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        printf("Remove proc pid: %d\n", pid);
        printf("Child send: %d\n", WEXITSTATUS(status));
    }
}


int main(int argc, char const *argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid = fork();
    if (pid == 0)
    {
        puts("Hi, I am child process.\n");
        sleep(10);
        return 12;
    }else
    {
        printf("Child proc id: %d\n", pid);
        pid = fork();
        if (pid == 0)
        {
            puts("Hi, I am child process.\n");
            sleep(10);
            exit(24);
        }else
        {
            int i;
            printf("Child proc id: %d\n", pid);
            for (i = 0; i < 5; i++)
            {
                puts("wait.......");
                sleep(5);
            }
        }    
    }
    
    return 0;
}
